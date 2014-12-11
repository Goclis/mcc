#pragma once
#include "mccsemanticerror.h"
#include <string>
using std::string;
/**
 * @report
 *	1. line number.
 *	2. parameter position in parameter list.
 *	3. function name.
 */
class MccMethodDefinitionLackParameterNameError :
	public MccSemanticError
{
public:
	MccMethodDefinitionLackParameterNameError(
		const string &fun_name, 
		int param_index);
	virtual ~MccMethodDefinitionLackParameterNameError(void);

	void report() const;

	string m_func_name;
	int m_param_index;
	int m_lineno;
};

