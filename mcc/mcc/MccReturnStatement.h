/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"

class MccReturnStatement :
	public MccStatement
{
public:
	MccReturnStatement(MccStatement *stmt);
	virtual ~MccReturnStatement(void);

private:
	MccStatement *m_stmt;
};

