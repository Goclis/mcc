#include "MccUndefinedVariableError.h"
#include <iostream>
using std::cout;


MccUndefinedVariableError::MccUndefinedVariableError(const string &name)
{
	m_var_name = name;
}


MccUndefinedVariableError::~MccUndefinedVariableError(void)
{
}


void MccUndefinedVariableError::report() const
{
	cout << "Line " << m_line_no << ": Undefined variable `"
		<< m_var_name << "`.\n";
}
