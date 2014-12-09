#include "MccAssignStatement.h"
#include "MccExpression.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"


MccAssignStatement::MccAssignStatement(
		MccExpression *left, 
		MccExpression *right, 
		bool is_port /*= false*/)
	: m_left_operand(left),
	  m_right_operand(right),
	  m_is_port(is_port)
{
	
}


MccAssignStatement::~MccAssignStatement(void)
{
	if (this->m_left_operand != nullptr) {
		delete this->m_left_operand;
	}

	if (this->m_right_operand != nullptr) {
		delete this->m_right_operand;
	}
}


int MccAssignStatement::generate_code() const
{
	string &code_buffer = theMccRobot().get_code_buffer();
	code_buffer += "MccAssignStatement generation.\n";

	// Gen(m_left_operand).
	this->m_left_operand->generate_code();

	// Push $v0.
	code_buffer += "sw $v0 0($sp)\n";
	code_buffer += "subiu $sp $sp 4\n";

	// Gen(m_right_operand).
	this->m_right_operand->generate_code();

	// Pop $v1.
	code_buffer += "lw $v1 4($sp)\n";
	code_buffer += "addiu $sp $sp 4\n";

	// Memory[$v1] = $v0.
	code_buffer += "sw $v0 0($v1)\n";

	return 0;
}


void MccAssignStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
