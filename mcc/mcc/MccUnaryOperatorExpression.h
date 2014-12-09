/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"
#include "MccPublicType.h"

class MccUnaryOperatorExpression :
	public MccExpression
{
public:
	MccUnaryOperatorExpression(void);
	MccUnaryOperatorExpression(UNARY_OPERATOR op, MccExpression *expr);
	virtual ~MccUnaryOperatorExpression(void);

	/**
	 * @brief Save the result of the unary expression into $v0.
	 */
	int generate_code() const;
	void semantic_detect();

	UNARY_OPERATOR m_operator;
	MccExpression *m_operand;
};

