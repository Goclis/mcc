#include "MccFuncParameter.h"
#include "MccIdentifier.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"


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


void MccFuncParameter::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}


void MccFuncParameter::set_lineno(int lineno)
{
	m_lineno = lineno;
}

int MccFuncParameter::get_lineno() const
{
	return m_lineno;
}
