#include "MccFunctionDeclaration.h"
#include "MccVariableDeclaration.h"
#include "MccFuncParameterList.h"
#include "MccStatementList.h"
#include "MccDeclarationList.h"
#include "MccStatement.h"
#include "MccFuncParameter.h"
#include "MccIdentifier.h"
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
	if (!m_contain_definition) {
		return 0;
	}

	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccFunctionDelcaration generation.\n";
#endif
	string func_label = get_decl_name();
	MccFunctionDeclaration *func_decl_bak = robot.get_current_func_decl();
	robot.set_current_func_decl(this);

	// Initialization.
	m_local_var_size = 0;
	m_parameter_size = 0;

	code_buffer += 
		func_label + ":\n";

	robot
		.add_code(func_label + ":");
	
	if ("interrupt0" == func_label || "interrupt1" == func_label
			|| "interrupt2" == func_label || "interrupt3" == func_label) {
		// Interrupt callback function (interrupt0~3), no parameter.
		// Push($v0).
		code_buffer +=
			"sw $v0, 0H($sp)\n"
			"addiu $v0, $zero, 1\n"
			"subu $sp, $sp, $v0\n";
		robot
			.add_code("sw $v0, 0H($sp)")
			.add_code("addiu $v0, $zero, 1")
			.add_code("subu $sp, $sp, $v0");
		// Push($v1).
		code_buffer +=
			"sw $v1, 0H($sp)\n"
			"addiu $v1, $zero, 1\n"
			"subu $sp, $sp, $v1\n";
		robot
			.add_code("sw $v1, 0H($sp)")
			.add_code("addiu $v1, $zero, 1")
			.add_code("subu $sp, $sp, $v1");
		// Push($fp) and set $fp.
		code_buffer +=
			"sw $t0, 0H($sp)\n"
			"addu $t0, $zero, $sp\n"
			"addiu $v0 $zero, 1\n"
			"subu $sp, $sp, $v0\n";
		robot
			.add_code("sw $t0, 0H($sp)")
			.add_code("addu $t0, $zero, $sp")
			.add_code("addiu $v0, $zero, 1")
			.add_code("subu $sp, $sp, $v0");

		// Iterate local variable declaration.
		for (size_t i = 0, len = this->m_local_variable_decls.size();
				i < len; ++i) {
			this->m_local_variable_decls[i]->generate_code();
		}

		// Iterate statement list.
		for (size_t i = 0, len = this->m_statement_list.size(); i < len; ++i) {
			this->m_statement_list[i]->generate_code();
		}

		// Retrieve local variables.
		code_buffer +=
			Utility::string_concat_int("addiu $sp, $sp, ", m_local_var_size) + "\n";
		robot
			.add_code(Utility::string_concat_int("addiu $sp, $sp, ", m_local_var_size));

		// Restore $fp $v0 $v1.
		code_buffer +=
			"lw $t0, 1H($sp)\n"
			"lw $v1, 2H($sp)\n"
			"lw $v0, 3H($sp)\n"
			"addiu $sp, $sp, 3\n"
			"eret\n";
		robot
			.add_code("lw $t0, 1H($sp)")
			.add_code("lw $v1, 2H($sp)")
			.add_code("lw $v0, 3H($sp)")
			.add_code("addiu $sp, $sp, 3")
			.add_code("eret");
	} else {
		// Iterate parameters, record position (positive offset of $fp).
		for (size_t i = 0, size = m_parameter_list.size(); i < size; ++i) {
			add_local_var_decl(
				m_parameter_list[i]->m_name->m_name,
				1,
				PARAMETER_VAR);
		}

		// Set $fp.
		code_buffer += 
			"addu $t0, $zero, $sp\n";
		robot
			.add_code("addu $t0, $zero, $sp");

		// Push $ra.
		code_buffer +=
			"sw $ra, 0H($sp)\n"
			"addiu $v0, $zero, 1\n"
			"subu $sp, $sp, $v0\n";
		robot
			.add_code("sw $ra, 0H($sp)")
			.add_code("addiu $v0, $zero, 1")
			.add_code("subu $sp, $sp, $v0");

		// Iterate local variable declaration.
		for (size_t i = 0, len = m_local_variable_decls.size();
				i < len; ++i) {
			m_local_variable_decls[i]->generate_code();
		}

		// Iterate statement list.
		for (size_t i = 0, len = m_statement_list.size(); i < len; ++i) {
			m_statement_list[i]->generate_code();
		}

		// Retrieve activation record.
		if (!m_has_retrieved) {
			// Retrieve local variables.
			if (m_local_var_size > 0) {
				code_buffer +=
					Utility::string_concat_int("addiu $sp, $sp, ", m_local_var_size) + "\n";
				robot
					.add_code(Utility::string_concat_int("addiu $sp, $sp, ", m_local_var_size));
			}

			// Restore $ra.
			code_buffer +=
				"lw $ra, 1H($sp)\n";
			robot
				.add_code("lw $ra, 1H($sp)");

			// Pop parameters, $ra and $fp.
			code_buffer +=
				Utility::string_concat_int("addiu $sp, $sp, ", m_parameter_size + 2) + "\n"
				"lw $t0, 0H($sp)\n"
				"jr $ra\n"
				"srlv $v1, $zero, $zero\n";
			robot
				.add_code(Utility::string_concat_int("addiu $sp, $sp, ", m_parameter_size + 2))
				.add_code("lw $t0, 0H($sp)")
				.add_code("jr $ra")
				.add_code("srlv $v1, $zero, $zero");
		}
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


void MccFunctionDeclaration::add_local_var_decl(
	const string &name, 
	int var_size,
	IdentifierType type)
{
	IdentifierInfo *new_info = new IdentifierInfo;
	new_info->scope = (void*) this;

	if (PARAMETER_VAR == type) {
		m_parameter_size += var_size;
		new_info->position = m_parameter_size;
		new_info->id_type = PARAMETER_VAR;
	} else {
		m_local_var_size += var_size;
		new_info->position = m_local_var_size;
		if (var_size > 1) {
			new_info->id_type = ARRAY_VAR;
		} else {
			new_info->id_type = NOMARL_VAR;
		}
	}

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
