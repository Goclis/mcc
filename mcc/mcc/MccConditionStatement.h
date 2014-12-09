/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"

class MccExpression;

class MccConditionStatement :
	public MccStatement
{
public:
	MccConditionStatement(MccExpression *condtion);
	virtual ~MccConditionStatement(void);

	MccExpression *m_condition;
};

