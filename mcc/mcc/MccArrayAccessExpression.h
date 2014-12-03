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
	MccArrayAccessExpression(MccIdentifier *id, MccExpression *index);
	virtual ~MccArrayAccessExpression(void);

	int generate_code() const;

private:
	MccIdentifier *m_id;
	MccExpression *m_index;
};

