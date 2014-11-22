/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"
#include <vector>

class MccIdentifier;

using std::vector;

class MccMethodCallExpression :
	public MccExpression
{
public:
	MccMethodCallExpression(void);
	virtual ~MccMethodCallExpression(void);

private:
	MccIdentifier *m_method_id;
	vector<MccExpression *> m_args;
};

