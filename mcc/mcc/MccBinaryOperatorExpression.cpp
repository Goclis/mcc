#include "MccBinaryOperatorExpression.h"


MccBinaryOperatorExpression::MccBinaryOperatorExpression(
		BINARY_OPERATOR op, 
		MccExpression *left, 
		MccExpression *right)
	: m_operator(op),
	  m_left_operand(left),
	  m_right_operand(right)
{
}


MccBinaryOperatorExpression::~MccBinaryOperatorExpression(void)
{
	if (this->m_left_operand != nullptr) {
		delete this->m_left_operand;
	}

	if (this->m_right_operand != nullptr) {
		delete this->m_right_operand;
	}
}
