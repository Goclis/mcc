/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"
#include <vector>

class MccIdentifier;
class MccExpressionList;

using std::vector;

class MccMethodCallExpression :
	public MccExpression
{
public:
	MccMethodCallExpression(MccIdentifier *id, MccExpressionList *expr_list);
	virtual ~MccMethodCallExpression(void);

private:
	MccIdentifier *m_method_id;
	vector<MccExpression *> m_args;
};

