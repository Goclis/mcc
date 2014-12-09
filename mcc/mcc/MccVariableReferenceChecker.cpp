#include "MccVariableReferenceChecker.h"
#include "MccUndefinedVariableError.h"
#include "MccVariableDeclaration.h"
#include "MccFunctionDeclaration.h"
#include "MccFuncParameter.h"
#include "MccIdentifier.h"
#include "MccStatement.h"
#include "MccAssignStatement.h"
#include "MccWhileStatement.h"
#include "MccIfStatement.h"
#include "MccBlockStatement.h"
#include "MccReturnStatement.h"
#include "MccExpression.h"
#include "MccBinaryOperatorExpression.h"
#include "MccUnaryOperatorExpression.h"
#include "MccMethodCallExpression.h"


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

	m_local_var_name.clear();
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
	for (size_t i = 0, len = stmt_list.size(); i < len; ++i) {
		stmt_list[i]->semantic_detect();
	}
}


void MccVariableReferenceChecker::detect(MccIfStatement *if_stmt)
{
	// Check condition, if_part and else_part (if have).
	if_stmt->m_condition->semantic_detect();
	if_stmt->m_if->semantic_detect();
	if (nullptr != if_stmt->m_else) {
		if_stmt->m_else->semantic_detect();
	}
}


void MccVariableReferenceChecker::detect(MccReturnStatement *rtn_stmt)
{
	rtn_stmt->m_expr->semantic_detect();
}


void MccVariableReferenceChecker::detect(MccBinaryOperatorExpression *binary_expr)
{
	binary_expr->m_left_operand->semantic_detect();
	binary_expr->m_right_operand->semantic_detect();
}


void MccVariableReferenceChecker::detect(MccUnaryOperatorExpression *unary_expr)
{
	unary_expr->m_operand->semantic_detect();
}


void MccVariableReferenceChecker::detect(MccMethodCallExpression *mc_expr)
{
	vector<MccExpression*> &expr_list = mc_expr->m_args;	
	for (size_t i = 0, len = expr_list.size(); i < len; ++i) {
		expr_list[i]->semantic_detect();
	}
}


void MccVariableReferenceChecker::detect(MccIdentifier *ident)
{
	bool found = false;
	for (size_t i = 0, len = m_local_var_name.size(); i < len; ++i) {
		if (m_local_var_name[i] == ident->m_name) {
			found = true;
			break;
		}
	}

	if (found) {
		return;
	}

	for (size_t i = 0, len = m_global_var_name.size(); i < len; ++i) {
		if (m_global_var_name[i] == ident->m_name) {
			found = true;
			break;
		}
	}

	if (!found) {
		m_error_list.push_back(new MccUndefinedVariableError(
			ident->m_name));
	}
}

