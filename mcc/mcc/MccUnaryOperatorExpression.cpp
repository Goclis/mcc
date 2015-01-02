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
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccUnaryOperatorExpression generation.\n";
#endif

	// Gen(m_operand).
	this->m_operand->generate_code();
	switch (this->m_operator)
	{
	case NEG_UNARY:
		code_buffer += 
			"nor $v0, $v0, $zero\n";
		robot
			.add_code("nor $v0, $v0, $zero");
		break;

	case NEGATIVE_UNARY:
		code_buffer += 
			"sub $v0, $zero, $v0\n";
		robot
			.add_code("sub $v0, $zero, $v0");
		break;

	case POSITIVE_UNARY:
#ifdef DEBUG_MODE
		code_buffer += "\t\t\t\t// Do nothing for +$v0";
#endif
		break;

	case NOT_UNARY:
		code_buffer += 
			"sltu $v0, $zero, $v0\n";
		robot
			.add_code("sltu $v0, $zero, $v0");
		break;

	case PORT_UNARY:
		code_buffer += 
			"lw $v0, 0H($v0)\n";
		robot
			.add_code("lw $v0, 0H($v0)");
		break;
	}
	return 0;
}


void MccUnaryOperatorExpression::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
