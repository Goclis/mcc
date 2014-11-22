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
	explicit MccFuncParameterList(MccFuncParameter *first) {}
	virtual ~MccFuncParameterList(void);

	void push_back(MccFuncParameter *param) {}

	vector<MccFuncParameter *> m_parameter_list;
};

