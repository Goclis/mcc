#include "MccAssignStatement.h"
#include "MccExpression.h"
#include "MccRobot.h"


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
	// cout << "MccAssignStatement generation." << endl;
	this->m_left_operand->generate_code();
	code_buffer += "sw $a0 0($sp)\n";
	code_buffer += "addiu $sp $sp -4\n";
	this->m_right_operand->generate_code();
	code_buffer += "sw $t0 4($sp)\n";
	code_buffer += "addiu $sp $sp 4\n";
	code_buffer += "sw $a0 0($t0)\n";

	return 0;
}
