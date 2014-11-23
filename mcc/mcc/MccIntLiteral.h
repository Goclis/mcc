/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"

class MccIntLiteral :
	public MccExpression
{
public:
	explicit MccIntLiteral(int value);
	virtual ~MccIntLiteral(void);

	/**
	 * @brief Get value of int literal.
	 */
	int get_value() const;

private:
	int m_value;
};

