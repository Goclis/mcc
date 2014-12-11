#include "MccMethodDefinitionLackParameterNameError.h"
#include <iostream>
using std::cout;


MccMethodDefinitionLackParameterNameError::MccMethodDefinitionLackParameterNameError(
	const string &fun_name, 
	int param_index)
{
	m_func_name = fun_name;
	m_param_index = param_index;
}


MccMethodDefinitionLackParameterNameError::~MccMethodDefinitionLackParameterNameError(void)
{
}


void MccMethodDefinitionLackParameterNameError::report() const
{
	cout << "Line " << m_lineno << ": The " << m_param_index 
		<< "th parameter of the function \""
		<< m_func_name << "\" lack name.\n";
}
