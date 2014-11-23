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
