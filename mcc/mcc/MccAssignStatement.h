/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "MccStatement.h"

class MccExpression;
class MccIdentifier;

/**
 * @brief Support assignment statement.
 *
 * @example
 *	a = 1
 *	a[1] = 1
 *	$a = 1
 */
class MccAssignStatement :
	public MccStatement
{
public:
	MccAssignStatement(
		MccExpression *right,
		MccIdentifier *identifier,
		MccExpression *array_index_expr = nullptr,
		MccExpression *port_expr = nullptr);
	virtual ~MccAssignStatement(void);

	int generate_code() const;
	void semantic_detect();

	/**
	 * @brief Right operand.
	 */
	MccExpression *m_right_operand;

	/**
	 * @brief For id based assignment.
	 *	a) a = 1;
	 *	b) a[1] = 1;
	 */
	MccIdentifier *m_identifier;

	/**
	 * @brief Port address expression.
	 *	a) $expr = 1;
	 */
	MccExpression *m_port_expr;

	/**
	 * @brief The index of the array assignment.
	 */
	MccExpression *m_array_index_expr;
};

