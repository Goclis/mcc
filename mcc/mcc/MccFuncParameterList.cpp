#include "MccFuncParameterList.h"


MccFuncParameterList::MccFuncParameterList(MccFuncParameter *first)
{
	this->push_back(first);
}


MccFuncParameterList::~MccFuncParameterList(void)
{
	// No need to release parameters, because they will be passed to other,
	// just clear list.
	this->m_parameter_list.clear();
}


void MccFuncParameterList::push_back(MccFuncParameter *param)
{
	if (param != nullptr) {
		this->m_parameter_list.push_back(param);
	}
}


void MccFuncParameterList::copy_to_list(vector<MccFuncParameter *> &list)
{
	for (size_t i = 0, len = this->m_parameter_list.size(); i < len; ++i) {
		list.push_back(this->m_parameter_list[i]);
	}
}
