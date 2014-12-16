#pragma once
#include "mccsemanticerror.h"
#include <string>
using std::string;


/**
 * @report
 *	1. Line number.
 *	2. Method name.
 */
class MccInvalidMethodNameError :
	public MccSemanticError
{
public:
	MccInvalidMethodNameError(const string &name);
	virtual ~MccInvalidMethodNameError(void);

	void report() const;

	int m_line_no;
	string m_func_name;
};

