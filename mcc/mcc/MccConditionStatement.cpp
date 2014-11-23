#include "MccConditionStatement.h"
#include "MccExpression.h"


MccConditionStatement::MccConditionStatement(MccExpression *condition)
	: m_condition(condition)
{
}


MccConditionStatement::~MccConditionStatement(void)
{
	if (this->m_condition != nullptr) {
		delete this->m_condition;
	}
}
