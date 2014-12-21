#include "MccReturnTypeChecker.h"
#include "MccReturnTypeError.h"
#include "MccFunctionDeclaration.h"
#include "MccReturnStatement.h"


MccReturnTypeChecker::MccReturnTypeChecker()
{
}


MccReturnTypeChecker::~MccReturnTypeChecker()
{
}


void MccReturnTypeChecker::detect(MccFunctionDeclaration *fun)
{
	// Don't check declaration.
	if (!fun->contain_definition()) {
		return;
	}

	// Set up current type.
	m_func_return_type = fun->get_type_spec();

	const vector<MccStatement*> stmt_list = fun->get_statement_list();
	for (size_t i = 0, size = stmt_list.size(); i < size; ++i) {
		stmt_list[i]->semantic_detect();
	}
}


void MccReturnTypeChecker::detect(MccReturnStatement *ret_stmt)
{
	TYPE_SPEC ret_type = (nullptr == ret_stmt->m_expr) ? VOID_TYPE_SPEC : INT_TYPE_SPEC;
	if (ret_type != m_func_return_type) {
		MccReturnTypeError *error = new MccReturnTypeError;
		error->m_line_no = ret_stmt->get_lineno();
		error->m_func_type = m_func_return_type;
		error->m_ret_type = ret_type;
		m_error_list.push_back(error);
	}
}
