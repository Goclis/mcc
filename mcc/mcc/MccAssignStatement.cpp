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