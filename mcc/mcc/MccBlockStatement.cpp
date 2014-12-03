#include "MccBlockStatement.h"


MccBlockStatement::MccBlockStatement(MccStatementList *stmt_list)
{
	if (stmt_list != nullptr) {
		stmt_list->copy_to_list(this->m_statement_list);
	}
}


MccBlockStatement::~MccBlockStatement(void)
{
	// Release all statements.
	for (size_t i = 0, len = this->m_statement_list.size(); i < len; ++i) {
		if (this->m_statement_list[i] != nullptr) {
			delete this->m_statement_list[i];
		}
	}
}


int MccBlockStatement::generate_code() const
{
	cout << "MccBlockStatement generation." << endl;
	for (size_t i = 0, len = this->m_statement_list.size(); i < len; ++i) {
		if (nullptr != this->m_statement_list[i]) {
			this->m_statement_list[i]->generate_code();
		}
	}

	return 0;
}
