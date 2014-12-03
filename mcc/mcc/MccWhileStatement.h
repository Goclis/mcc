/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccconditionstatement.h"

class MccWhileStatement :
	public MccConditionStatement
{
public:
	MccWhileStatement(MccExpression *condition, MccStatement *stmt);
	virtual ~MccWhileStatement(void);

	int generate_code() const;

private:
	MccStatement *m_statement;
};

