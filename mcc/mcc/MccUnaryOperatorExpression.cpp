#include "MccUnaryOperatorExpression.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"


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
	string &code_buffer = theMccRobot().get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccUnaryOperatorExpression generation.\n";
#endif

	// Gen(m_operand).
	this->m_operand->generate_code();
	switch (this->m_operator)
	{
	case NEG_UNARY:
		code_buffer += "nor $v0 $v0 $zero\n";
		break;

	case NEGATIVE_UNARY:
		code_buffer += "subu $v0 $zero $v0\n";
		break;

	case POSITIVE_UNARY:
#ifdef DEBUG_MODE
		code_buffer += "\t\t\t\t// Do nothing for +$v0";
#endif
		break;

	case NOT_UNARY:
		code_buffer += "sltu $v0 $zero $v0\n";
		break;

	case PORT_UNARY:
		code_buffer += "lw $v0 0($v0)\n";
		break;
	}
	return 0;
}


void MccUnaryOperatorExpression::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
