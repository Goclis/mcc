/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"

class MccExpression;

/**
 * @brief Support return statement.
 *
 * @example
 *	return
 *	return 1 + 1
 */
class MccReturnStatement :
	public MccStatement
{
public:
	MccReturnStatement(MccExpression *expr);
	virtual ~MccReturnStatement(void);

	int generate_code() const;
	void semantic_detect();

	MccExpression *m_expr;
};

