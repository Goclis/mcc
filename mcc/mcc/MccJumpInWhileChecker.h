#pragma once
#include "mccsemanticerrorchecker.h"

class MccFunctionDeclaration;
class MccWhileStatement;
class MccBlockStatement;
class MccContinueStatement;
class MccBreakStatement;

/**
 * @brief Check whether a while block exists out of
 *	a break or continue statement.
 */
class MccJumpInWhileChecker :
	public MccSemanticErrorChecker
{
public:
	MccJumpInWhileChecker(void);
	virtual ~MccJumpInWhileChecker(void);
	
	void detect(MccFunctionDeclaration *fun);
	void detect(MccWhileStatement *while_stmt);
	void detect(MccBlockStatement *block_stmt);
	void detect(MccBreakStatement *brk_stmt);
	void detect(MccContinueStatement *ctn_stmt);

private:
	/**
	 * @brief the current while block numbers.
	 */
	int m_while_level;
};

