#include "MccJumpOutOfWhileError.h"
#include <iostream>
using std::cout;


MccJumpOutOfWhileError::MccJumpOutOfWhileError(StatementType stmt_type)
	: m_stmt_type(stmt_type)
{
	
}


MccJumpOutOfWhileError::~MccJumpOutOfWhileError(void)
{
}


void MccJumpOutOfWhileError::report() const
{
	cout << "Line " << m_lineno << ": " 
		<< ((m_stmt_type == BREAK_STMT) ? "break" : "continue")
		<< " statement should inside while statement\n";
}
