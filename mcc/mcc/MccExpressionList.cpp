#include "MccExpressionList.h"


MccExpressionList::MccExpressionList(MccExpression *first)
{
	this->push_back(first);
}


MccExpressionList::~MccExpressionList(void)
{
	// No need to release expressions, because they will be passed to other,
	// just clear list.
	this->m_expr_list.clear();
}


void MccExpressionList::push_back(MccExpression *expr)
{
	if (expr != nullptr) {
		this->m_expr_list.push_back(expr);
	}
}


void MccExpressionList::copy_to_list(vector<MccExpression *> &list)
{
	for (size_t i = 0, len = this->m_expr_list.size(); i < len; ++i) {
		list.push_back(this->m_expr_list[i]);
	}
}
