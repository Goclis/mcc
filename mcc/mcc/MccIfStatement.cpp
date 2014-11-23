#include "MccIfStatement.h"


MccIfStatement::MccIfStatement(
		MccExpression *condition, 
		MccStatement *if_part, 
		MccStatement *else_part)
	: MccConditionStatement(condition),
	  m_if(if_part),
	  m_else(else_part)
{
}


MccIfStatement::~MccIfStatement(void)
{
	if (this->m_if != nullptr) {
		delete this->m_if;
	}

	if (this->m_else != nullptr) {
		delete this->m_else;
	}
}
