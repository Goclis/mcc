#include "MccVariableReferenceChecker.h"
#include "MccVariableDeclaration.h"
#include "MccFunctionDeclaration.h"
#include "MccFuncParameter.h"
#include "MccIdentifier.h"
#include "MccStatement.h"
#include "MccAssignStatement.h"
#include "MccWhileStatement.h"
#include "MccBlockStatement.h"
#include "MccExpression.h"


MccVariableReferenceChecker::MccVariableReferenceChecker(void)
{
	m_current_scope = nullptr;
}


MccVariableReferenceChecker::~MccVariableReferenceChecker(void)
{
}


void MccVariableReferenceChecker::detect(MccVariableDeclaration *var)
{
	string var_name = var->get_decl_name();
	if (nullptr == m_current_scope) {
		m_global_var_name.push_back(var_name);
	} else {
		m_local_var_name.push_back(var_name);
	}
}

void MccVariableReferenceChecker::detect(MccFunctionDeclaration *fun)
{
	if (!fun->contain_definition()) {
		return;
	}

	// Parameters are local variables.
	const vector<MccFuncParameter*>& param_list = fun->get_parameter_list();
	for (size_t i = 0, len = param_list.size(); i < len; ++i) {
		m_local_var_name.push_back(param_list[i]->m_name->m_name);
	}
	
	// Local variable declaration need to detect (add to available list).
	const vector<MccVariableDeclaration*>& local_decls = fun->get_local_variable_decls();
	for (size_t i = 0, len = local_decls.size(); i < len; ++i) {
		local_decls[i]->semantic_detect();
	}

	// Check statements.
	const vector<MccStatement*>& stmt_list = fun->get_statement_list();
	for (size_t i = 0, len = stmt_list.size(); i < len; ++i) {
		stmt_list[i]->semantic_detect();
	}
}


void MccVariableReferenceChecker::detect(MccAssignStatement *assign_stmt)
{
	// Check left expression and right expression.
	assign_stmt->m_left_operand->semantic_detect();
	assign_stmt->m_right_operand->semantic_detect();
}


void MccVariableReferenceChecker::detect(MccWhileStatement *while_stmt)
{
	// Check condition and body.
	while_stmt->m_condition->semantic_detect();
	while_stmt->m_statement->semantic_detect();
}


void MccVariableReferenceChecker::detect(MccBlockStatement *block_stmt)
{
	// Iterate all statement.
	vector<MccStatement*> &stmt_list = block_stmt->m_statement_list;

}

