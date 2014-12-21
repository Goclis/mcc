#include "MccReturnTypeError.h"
#include <iostream>
using std::cout;


MccReturnTypeError::MccReturnTypeError()
{
}


MccReturnTypeError::~MccReturnTypeError()
{
}


void MccReturnTypeError::report() const
{
	cout << "Line " << m_line_no << ": Return type is incompatible with function. "
		<< "Function: " << (m_func_type == VOID_TYPE_SPEC ? "void" : "int") << " "
		<< "Return type: " << (m_ret_type == VOID_TYPE_SPEC ? "void" : "int") << "\n";
}
