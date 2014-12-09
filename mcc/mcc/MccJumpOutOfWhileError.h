#pragma once
#include "mccsemanticerror.h"

/**
 * @report
 *	1. line number of the statement.
 *	2. type of the statement, BREAK or CONTINUE.
 */
class MccJumpOutOfWhileError :
	public MccSemanticError
{
public:
	enum StatementType {
		BREAK_STMT,
		CONTINUE_STMT
	};

	MccJumpOutOfWhileError(StatementType stmt_type);
	virtual ~MccJumpOutOfWhileError(void);

	void report() const;

	StatementType m_stmt_type;
};

