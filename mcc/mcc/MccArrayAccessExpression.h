/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"

class MccIdentifier;

class MccArrayAccessExpression :
	public MccExpression
{
public:
	MccArrayAccessExpression(void);
	virtual ~MccArrayAccessExpression(void);

private:
	MccIdentifier *m_id;
	MccExpression *m_index;
};

