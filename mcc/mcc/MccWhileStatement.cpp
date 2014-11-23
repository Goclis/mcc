#include "MccWhileStatement.h"


MccWhileStatement::MccWhileStatement(MccExpression *condition, MccStatement *stmt)
	: MccConditionStatement(condition),
	  m_statement(stmt)
{
}


MccWhileStatement::~MccWhileStatement(void)
{
	if (this->m_statement != nullptr) {
		delete this->m_statement;
	}
}
