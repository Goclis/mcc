/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccExpression;

using std::vector;

class MccExpressionList
{
public:
	MccExpressionList(MccExpression *first);
	virtual ~MccExpressionList(void);

	void push_back(MccExpression *expr) {}

	vector<MccExpression *> m_expr_list;
};

