#pragma once
#include "mccsemanticerror.h"
#include <string>
using std::string;

/**
 * @report
 *	1. line number of the variable.
 *	2. variable name.
 */
class MccUndefinedVariableError :
	public MccSemanticError
{
public:
	MccUndefinedVariableError(const string &name);
	virtual ~MccUndefinedVariableError(void);

	void report() const;

	string m_var_name;
	int m_line_no;
};

