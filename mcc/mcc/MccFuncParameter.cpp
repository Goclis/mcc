#include "MccFuncParameter.h"
#include "MccIdentifier.h"


MccFuncParameter::MccFuncParameter(
	TYPE_SPEC type_spec, 
	MccIdentifier *id /*= nullptr*/, 
	int array_size /*= -1*/)
	: m_type_spec(type_spec),
	  m_name(id),
	  m_array_size(array_size)
{
	
}


MccFuncParameter::~MccFuncParameter(void)
{
	if (this->m_name != nullptr) {
		delete this->m_name;
	}
}
