/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccconditionstatement.h"

class MccIfStatement :
	public MccConditionStatement
{
public:
	MccIfStatement(
		MccExpression *condition, 
		MccStatement *if_part, 
		MccStatement *else_part = nullptr);
	virtual ~MccIfStatement(void);

	int generate_code() const;
	void semantic_detect();

	MccStatement *m_if;
	MccStatement *m_else;
};

