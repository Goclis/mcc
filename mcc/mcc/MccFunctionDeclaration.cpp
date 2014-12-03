#include "MccFunctionDeclaration.h"
#include "MccVariableDeclaration.h"
#include "MccFuncParameterList.h"
#include "MccStatementList.h"
#include "MccDeclarationList.h"
#include "MccStatement.h"
#include "MccFuncParameter.h"
#include "MccRobot.h"
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
	cout << "MccFunctionDelcaration generation." << endl;

	string func_label = this->get_decl_name();
	IdentifierInfo *info = theMccRobot().add_global_decl(func_label, 0);

	if (!this->m_contain_definition) {
		return 0;
	}

	theMccRobot().set_current_func_decl(this);
	// Initialization.
	this->m_ar_size = 0;
	this->m_local_var_size = 0;

	// Each parameter is an address in function activation record.
	this->m_ar_size = 4 * this->m_parameter_list.size();
	this->m_ar_size += 4; // The old frame pointer.
	this->m_ar_size += 4; // $ra, return address.

	cout << func_label << ":" << endl;

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
			cout << "addiu $sp $sp " << this->m_local_var_size << endl;
		}
		cout << "lw $ra 4($sp)" << endl;
		cout << "addiu $sp $sp " << this->m_ar_size - this->m_local_var_size << endl;
		cout << "lw $fp 0($sp)" << endl;
		cout << "jr $ra" << endl;
	}

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
		= Utility::string_concat_int("$fp - ", this->m_local_var_size);
	if (var_size > 4) {
		new_info->id_type = ARRAY_VAR;
	} else {
		new_info->id_type = NOMARL_VAR;
	}
	this->m_ar_size += var_size;

	this->m_local_identifiers.insert(IdentifierMap::value_type(name, new_info));

	cout << "subiu $sp $sp " << var_size << endl;
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
