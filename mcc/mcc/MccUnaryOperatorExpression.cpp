#include "MccUnaryOperatorExpression.h"
#include "MccRobot.h"


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
	// cout << "MccUnaryOperatorExpression generation." << endl;
	string &code_buffer = theMccRobot().get_code_buffer();
	this->m_operand->generate_code();
	switch (this->m_operator)
	{
	case NEG_UNARY:
		code_buffer += "mov $a0 !$a0\n";
		break;

	case NEGATIVE_UNARY:
		code_buffer += "mov $a0 -$a0\n";
		break;

	case POSITIVE_UNARY:
		code_buffer += "// mov $a0 $a0\n";
		break;

	case NOT_UNARY:
		code_buffer += "mov $a0 ~$a0\n";
		break;

	case PORT_UNARY:
		code_buffer += "mov $a0 PORT($a0)\n";
		break;
	}
	return 0;
}
