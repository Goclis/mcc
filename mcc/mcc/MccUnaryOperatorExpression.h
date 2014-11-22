/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"

class MccUnaryOperatorExpression :
	public MccExpression
{
public:
	enum UNARY_OPERATOR {

	};

	MccUnaryOperatorExpression(void);
	virtual ~MccUnaryOperatorExpression(void);

private:
	UNARY_OPERATOR m_operator;
	MccExpression *m_operand;
};

