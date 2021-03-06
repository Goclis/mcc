/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"
#include "MccPublicType.h"

/**
 * @brief Support binary operator expression.
 *
 * @example
 *	1 + 1
 *	1 * 1
 *	1 / 1
 *	...
 */
class MccBinaryOperatorExpression :
	public MccExpression
{
public:
	MccBinaryOperatorExpression(
		BINARY_OPERATOR op, 
		MccExpression *left, 
		MccExpression *right);
	virtual ~MccBinaryOperatorExpression(void);

	/**
	 * @brief Save the result of the binary expression into return register.
	 */
	int generate_code() const;
	void semantic_detect();

	BINARY_OPERATOR m_operator;
	MccExpression *m_left_operand;
	MccExpression *m_right_operand;
};

