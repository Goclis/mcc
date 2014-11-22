/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccFuncParameter;

using std::vector;

class MccFuncParameterList
{
public:
	MccFuncParameterList(void);
	virtual ~MccFuncParameterList(void);

	vector<MccFuncParameter *> m_parameter_list;
};

