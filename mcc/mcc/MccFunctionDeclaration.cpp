#include "MccFunctionDeclaration.h"
#include "MccVariableDeclaration.h"
#include "MccFuncParameterList.h"
#include "MccStatementList.h"
#include "MccDeclarationList.h"
#include "MccStatement.h"
#include "MccFuncParameter.h"


MccFunctionDeclaration::MccFunctionDeclaration(
		TYPE_SPEC type_spec, 
		MccIdentifier *identifier, 
		MccFuncParameterList *params, 
		MccDeclarationList *decls, 
		MccStatementList *stmts)
	: MccDeclaration(type_spec, identifier)
{
	this->m_if_levels = 0;
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

	// Identifier released by base class destructor.
}


int MccFunctionDeclaration::generate_code()
{
	// Each parameter is an address in function activation record.
	this->m_ar_size = 4 * this->m_parameter_list.size();

	for (size_t i = 0, len = this->m_local_variable_decls.size();
			i < len; ++i) {
		this->m_ar_size += this->m_local_variable_decls[i]->generate_code();
	}

	for (size_t i = 0, len = this->m_statement_list.size(); i < len; ++i) {
		this->m_statement_list[i]->generate_code();
	}

	return 0;
}


int MccFunctionDeclaration::get_if_levels() const
{
	return this->m_if_levels;
}


void MccFunctionDeclaration::increase_if_level()
{
	++this->m_if_levels;
}


void MccFunctionDeclaration::decrease_if_level()
{
	--this->m_if_levels;
}


void MccFunctionDeclaration::set_has_retrieved()
{
	this->m_has_retrieved = true;
}


int MccFunctionDeclaration::get_ar_size() const
{
	return this->m_ar_size;
}
