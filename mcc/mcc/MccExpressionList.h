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
	MccExpressionList(void);
	virtual ~MccExpressionList(void);

	vector<MccExpression *> m_expr_list;
};

