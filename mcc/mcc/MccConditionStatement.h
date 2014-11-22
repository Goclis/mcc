/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"
#include "MccExpression.h"

class MccConditionStatement :
	public MccStatement
{
public:
	MccConditionStatement(void);
	virtual ~MccConditionStatement(void);

protected:
	MccExpression *m_condition;
};

