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
	MccIfStatement(void);
	virtual ~MccIfStatement(void);

private:
	MccStatement *m_if;
	MccStatement *m_else;
};

