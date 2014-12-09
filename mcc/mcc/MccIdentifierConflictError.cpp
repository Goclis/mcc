#include "MccIdentifierConflictError.h"
#include <iostream>
using std::cout;


MccIdentifierConflictError::MccIdentifierConflictError(const string &name)
{
	m_id_name = name;
	m_line_no_cause_conflict = 0;
	m_line_no_having_conflict = 0;
}


MccIdentifierConflictError::~MccIdentifierConflictError(void)
{
}

void MccIdentifierConflictError::report() const
{
	cout << "Identifier `" << m_id_name << "` conflict: "
		<< "line " << m_line_no_cause_conflict << " and "
		<< "line " << m_line_no_having_conflict << "\n";
}