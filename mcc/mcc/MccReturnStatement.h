/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"

class MccExpression;

class MccReturnStatement :
	public MccStatement
{
public:
	MccReturnStatement(MccExpression *expr);
	virtual ~MccReturnStatement(void);

	int generate_code() const;

private:
	MccExpression *m_expr;
};

