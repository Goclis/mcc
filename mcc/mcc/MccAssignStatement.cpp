#include "MccAssignStatement.h"
#include "MccExpression.h"


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
	cout << "MccAssignStatement generation." << endl;
	this->m_left_operand->generate_code();
	cout << "sw $a0 0($sp)" << endl;
	cout << "addiu $sp $sp -4" << endl;
	this->m_right_operand->generate_code();
	cout << "sw $t0 4($sp)" << endl;
	cout << "addiu $sp $sp 4" << endl;
	cout << "sw $a0 0($t0)" << endl;

	return 0;
}
