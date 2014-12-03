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


int MccUnaryOperatorExpression::generate_code() const
{
	cout << "MccUnaryOperatorExpression generation." << endl;
	this->m_operand->generate_code();
	switch (this->m_operator)
	{
	case NEG_UNARY:
		break;

	case NEGATIVE_UNARY:
		break;

	case POSITIVE_UNARY:
		break;

	case NOT_UNARY:
		break;

	case PORT_UNARY:
		break;
	}
	return 0;
}
