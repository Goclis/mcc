/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "MccStatement.h"

class MccExpression;

class MccAssignStatement :
	public MccStatement
{
public:
	MccAssignStatement(
		MccExpression *left, 
		MccExpression *right, 
		bool is_port = false);
	virtual ~MccAssignStatement(void);

	int generate_code() const;
	void semantic_detect();


	/**
	 * @brief Left operand. According to yacc grammar, 
	 *	it will be one of the following expressions.
	 *	a) Identifier
	 *	b) ArrayAccessExpression
	 *	c) UnaryOperatorExpression
	 */
	MccExpression *m_left_operand;

	/**
	 * @brief Right operand.
	 */
	MccExpression *m_right_operand;

	/**
	 * @brief Indicate that whether the statement is port assignment.
	 */
	bool m_is_port;
};

