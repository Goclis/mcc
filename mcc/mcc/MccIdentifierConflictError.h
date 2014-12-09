#pragma once
#include "mccsemanticerror.h"
#include <string>
using std::string;

/**
 * @report
 *	1. line number of the identifer having conflict
 *	2. line number of the identifer causing conflict
 *	3. identifier name
 */
class MccIdentifierConflictError :
	public MccSemanticError
{
public:
	MccIdentifierConflictError(const string &name);
	virtual ~MccIdentifierConflictError(void);

	void report() const;

	int m_line_no_having_conflict;
	int m_line_no_cause_conflict;
	string m_id_name;
};

