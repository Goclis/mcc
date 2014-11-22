#include "MccUnaryOperatorExpression.h"


MccUnaryOperatorExpression::MccUnaryOperatorExpression(void)
	: m_operand(nullptr)
{
}


MccUnaryOperatorExpression::MccUnaryOperatorExpression(UNARY_OPERATOR op, MccExpression *expr)
	: m_operator(op),
	  m_operand(expr)
{

}


MccUnaryOperatorExpression::~MccUnaryOperatorExpression(void)
{
	if (this->m_operand != nullptr) {
		delete this->m_operand;
	}
}
