#include "MccVariableTypeError.h"
#include <iostream>
using std::cout;


MccVariableTypeError::MccVariableTypeError(const string &id_name)
	: m_id_name(id_name)
{
}


MccVariableTypeError::~MccVariableTypeError(void)
{
}


void MccVariableTypeError::report() const
{
	cout << "The type of the identifier \"" << m_id_name
		<< "\" cannot be void.\n";
}
