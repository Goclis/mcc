#include "MccJumpInWhileChecker.h"
#include "MccJumpOutOfWhileError.h"
#include "MccFunctionDeclaration.h"
#include "MccWhileStatement.h"
#include "MccBreakStatement.h"
#include "MccContinueStatement.h"
#include "MccBlockStatement.h"


MccJumpInWhileChecker::MccJumpInWhileChecker(void)
{
	m_while_level = 0;
}


MccJumpInWhileChecker::~MccJumpInWhileChecker(void)
{
}


void MccJumpInWhileChecker::detect(MccFunctionDeclaration *fun)
{
	// Iterate each statement.
	const vector<MccStatement*> stmt_list = fun->get_statement_list();
	for (size_t i = 0, len = stmt_list.size(); i < len; ++i) {
		stmt_list[i]->semantic_detect();
	}
}


void MccJumpInWhileChecker::detect(MccWhileStatement *while_stmt)
{
	// Detect the statement inside it.
	++m_while_level;
	while_stmt->m_statement->semantic_detect();
	--m_while_level;
}


void MccJumpInWhileChecker::detect(MccBlockStatement *block_stmt)
{
	// Detect the statament list.
	const vector<MccStatement*>& stmt_list = block_stmt->m_statement_list;
	for (size_t i = 0, len = stmt_list.size(); i < len; ++i) {
		stmt_list[i]->semantic_detect();
	}
}


void MccJumpInWhileChecker::detect(MccBreakStatement *brk_stmt)
{
	if (0 == m_while_level) {
		MccJumpOutOfWhileError *error = new MccJumpOutOfWhileError(
			MccJumpOutOfWhileError::BREAK_STMT);
		error->m_lineno = brk_stmt->get_lineno();
		m_error_list.push_back(error);
	}
}


void MccJumpInWhileChecker::detect(MccContinueStatement *ctn_stmt)
{
	if (0 == m_while_level) {
		MccJumpOutOfWhileError *error = new MccJumpOutOfWhileError(
			MccJumpOutOfWhileError::CONTINUE_STMT);
		error->m_lineno = ctn_stmt->get_lineno();
		m_error_list.push_back(error);
	}
}

