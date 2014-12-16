#include "MccInvalidMethodNameError.h"
#include <iostream>
using std::cout;


MccInvalidMethodNameError::MccInvalidMethodNameError(const string &name)
	: m_func_name(name)
{
}


MccInvalidMethodNameError::~MccInvalidMethodNameError(void)
{
}


void MccInvalidMethodNameError::report() const
{
	cout << "Line " << m_line_no << ": "
		<< "The name of function `" << m_func_name << "` is invalid "
		<< "(Cannot be label + number).\n";
}
