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
	MccWhileStatement(void);
	virtual ~MccWhileStatement(void);

private:
	MccStatement *m_statement;
};

