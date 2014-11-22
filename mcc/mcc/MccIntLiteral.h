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
	MccIntLiteral(void);
	explicit MccIntLiteral(int value);
	virtual ~MccIntLiteral(void);

private:
	int m_value;
};

