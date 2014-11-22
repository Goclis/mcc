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

	int get_value() const {return this->m_value;}

private:
	int m_value;
};

