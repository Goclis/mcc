/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"

class MccBinaryOperatorExpression :
	public MccExpression
{
public:
	enum BINARY_OPERATOR {

	};

	MccBinaryOperatorExpression(void);
	virtual ~MccBinaryOperatorExpression(void);

private:
	BINARY_OPERATOR m_operator;
	MccExpression *m_left_operand;
	MccExpression *m_right_operand;
};

