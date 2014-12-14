/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"

class MccIdentifier;

/**
 * @brief Support array access expression.
 *
 * @example
 *	a[1]
 *	a[1+1]
 */
class MccArrayAccessExpression :
	public MccExpression
{
public:
	MccArrayAccessExpression(void);
	MccArrayAccessExpression(MccIdentifier *id, MccExpression *index);
	virtual ~MccArrayAccessExpression(void);

	/**
	 * @brief Save the value into the $v0.
	 */
	int generate_code() const;

private:
	MccIdentifier *m_id;
	MccExpression *m_index;
};

