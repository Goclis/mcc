#include "MccFunctionDeclaration.h"
#include "MccVariableDeclaration.h"
#include "MccFuncParameterList.h"
#include "MccStatementList.h"
#include "MccDeclarationList.h"
#include "MccStatement.h"
#include "MccFuncParameter.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"
#include "Utility.h"


MccFunctionDeclaration::MccFunctionDeclaration(
		TYPE_SPEC type_spec, 
		MccIdentifier *identifier, 
		MccFuncParameterList *params, 
		MccDeclarationList *decls, 
		MccStatementList *stmts)
	: MccDeclaration(type_spec, identifier)
{
	this->m_condition_block_levels = 0;
	this->m_has_retrieved = false;

	if (params != nullptr) {
		params->copy_to_list(this->m_parameter_list);
	}

	if (decls == nullptr && stmts == nullptr) {
		this->m_contain_definition = false;
	} else {
		if (decls != nullptr) {
			decls->copy_to_list_derived(this->m_local_variable_decls);
		}
		if (stmts != nullptr) {
			stmts->copy_to_list(this->m_statement_list);
		}
		this->m_contain_definition = true;
	}
}


MccFunctionDeclaration::~MccFunctionDeclaration(void)
{
	// Release all local variable declarations.
	for (size_t i = 0, len = this->m_local_variable_decls.size();
			i < len; ++i) {
		if (this->m_local_variable_decls[i]) {
			delete this->m_local_variable_decls[i];
		}
	}

	// Release all parameters.
	for (size_t i = 0, len = this->m_parameter_list.size(); i < len; ++i) {
		if (this->m_parameter_list[i]) {
			delete this->m_parameter_list[i];
		}
	}

	// Release all statements.
	for (size_t i = 0, len = this->m_statement_list.size(); i < len; ++i) {
		if (this->m_statement_list[i]) {
			delete this->m_statement_list[i];
		}
	}

	// Release the map of local variable declarations.
	for (IdentifierMap::iterator iter = this->m_local_identifiers.begin(),
			the_end = this->m_local_identifiers.end(); iter != the_end; ++iter) {
		delete iter->second;
	}

	// Identifier released by base class destructor.
}


int MccFunctionDeclaration::generate_code()
{
	if (!this->m_contain_definition) {
		return 0;
	}

	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	code_buffer += "MccFunctionDelcaration generation.\n";
	string func_label = this->get_decl_name();
	MccFunctionDeclaration *func_decl_bak = robot.get_current_func_decl();
	robot.set_current_func_decl(this);

	// Initialization.
	this->m_ar_size = 0;
	this->m_local_var_size = 0;

	// Each parameter is an address in function activation record.
	this->m_ar_size = 4 * this->m_parameter_list.size();
	this->m_ar_size += 4; // The old frame pointer.
	this->m_ar_size += 4; // $ra, return address.

	code_buffer += func_label + ":\n";

	// Iterate local variable declaration.
	for (size_t i = 0, len = this->m_local_variable_decls.size();
			i < len; ++i) {
		this->m_local_variable_decls[i]->generate_code();
	}
	
	// Iterate statement list.
	for (size_t i = 0, len = this->m_statement_list.size(); i < len; ++i) {
		this->m_statement_list[i]->generate_code();
	}

	// If no return statement at last, need to generate code to retrieving 
	// activation record.
	if (!this->m_has_retrieved) {
		if (this->m_local_var_size > 0) {
			code_buffer
				+= Utility::string_concat_int("addiu $sp $sp ", this->m_local_var_size)
				+ "\n";
		}
		code_buffer += "lw $ra 4($sp)\n";
		code_buffer 
			+= Utility::string_concat_int("addiu $sp $sp ",
				this->m_ar_size - this->m_local_var_size) + "\n";
		code_buffer += "lw $fp 0($sp)\n";
		code_buffer += "jr $ra\n";
	}

	robot.set_current_func_decl(func_decl_bak);

	return 0;
}


int MccFunctionDeclaration::get_cond_stmt_level() const
{
	return this->m_condition_block_levels;
}


void MccFunctionDeclaration::increase_cond_stmt_level()
{
	++this->m_condition_block_levels;
}


void MccFunctionDeclaration::decrease_cond_stmt_level()
{
	--this->m_condition_block_levels;
}


void MccFunctionDeclaration::set_has_retrieved()
{
	this->m_has_retrieved = true;
}


int MccFunctionDeclaration::get_ar_size() const
{
	return this->m_ar_size;
}


void MccFunctionDeclaration::add_local_var_decl(const string &name, int var_size)
{
	IdentifierInfo *new_info = new IdentifierInfo;
	this->m_local_var_size += var_size;
	new_info->position
		= Utility::string_concat_int("", this->m_local_var_size);
	if (var_size > 4) {
		new_info->id_type = ARRAY_VAR;
	} else {
		new_info->id_type = NOMARL_VAR;
	}
	this->m_ar_size += var_size;

	this->m_local_identifiers.insert(IdentifierMap::value_type(name, new_info));
}


int MccFunctionDeclaration::get_vars_size() const
{
	return this->m_local_var_size;
}


IdentifierInfo* MccFunctionDeclaration::get_identifier_info(const string &name)
{
	IdentifierMap::iterator iter = this->m_local_identifiers.find(name);
	if (iter != this->m_local_identifiers.end()) {
		return iter->second;
	} else {
		return nullptr;
	}
}


IdentifierInfo* MccFunctionDeclaration::search_identifier_info(const string &name)
{
	IdentifierInfo *info = this->get_identifier_info(name);
	if (nullptr == info) {
		return theMccRobot().get_identifier_info(name);
	} else {
		return info;
	}
}


void MccFunctionDeclaration::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}


const vector<MccVariableDeclaration*>& MccFunctionDeclaration::get_local_variable_decls()
{
	return m_local_variable_decls;
}


bool MccFunctionDeclaration::is_definition() const
{
	return m_contain_definition;
}


const vector<MccFuncParameter*>& MccFunctionDeclaration::get_parameter_list()
{
	return m_parameter_list;
}


const vector<MccStatement*>& MccFunctionDeclaration::get_statement_list()
{
	return m_statement_list;
}


bool MccFunctionDeclaration::contain_definition() const
{
	return m_contain_definition;
}
