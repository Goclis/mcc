#include "MccReturnStatement.h"

MccReturnStatement::MccReturnStatement(MccStatement *stmt)
	: m_stmt(stmt)
{

}

MccReturnStatement::~MccReturnStatement()
{
	if (this->m_stmt != nullptr) {
		delete this->m_stmt;
	}	
}