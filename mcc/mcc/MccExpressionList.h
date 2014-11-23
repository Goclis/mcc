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

	/**
	 * @brief Same as vector::push_back.
	 */
	void push_back(MccExpression *expr);

	/**
	 * @brief Copy content to other list.
	 *
	 * @param list Destination list.
	 */
	void copy_to_list(vector<MccExpression *> &list);

private:
	vector<MccExpression *> m_expr_list;
};

