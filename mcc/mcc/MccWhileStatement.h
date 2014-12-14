/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccconditionstatement.h"

/**
 * @brief Support while statement.
 *
 * @example
 *	while () ...
 *	while () {}
 */
class MccWhileStatement :
	public MccConditionStatement
{
public:
	MccWhileStatement(MccExpression *condition, MccStatement *stmt);
	virtual ~MccWhileStatement(void);

	int generate_code() const;
	void semantic_detect();

	MccStatement *m_statement;
};

