#include "MccMethodCallExpression.h"
#include "MccExpressionList.h"
#include "MccIdentifier.h"


MccMethodCallExpression::MccMethodCallExpression(MccIdentifier *id, MccExpressionList *expr_list)
	: m_method_id(id)
{
	if (expr_list != nullptr) {
		expr_list->copy_to_list(this->m_args);
	}
}


MccMethodCallExpression::~MccMethodCallExpression(void)
{
	if (this->m_method_id != nullptr) {
		delete this->m_method_id;
	}

	for (size_t i = 0, len = this->m_args.size(); i < len; ++i) {
		if (this->m_args[i]) {
			delete this->m_args[i];
		}
	}
}
