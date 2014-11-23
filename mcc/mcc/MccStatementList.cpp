#include "MccStatementList.h"


MccStatementList::MccStatementList(MccStatement *first)
{
}


MccStatementList::~MccStatementList(void)
{
}


void MccStatementList::push_back(MccStatement *stmt)
{
	if (stmt != nullptr) {
		this->m_stmt_list.push_back(stmt);
	}
}


void MccStatementList::copy_to_list(vector<MccStatement *> &list)
{
	for (size_t i = 0, len = this->m_stmt_list.size(); i < len; ++i) {
		list.push_back(this->m_stmt_list[i]);
	}
}
