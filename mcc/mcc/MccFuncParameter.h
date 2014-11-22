/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include "MccPublicType.h"

class MccIdentifier;

class MccFuncParameter
{
public:
	MccFuncParameter(void);
	MccFuncParameter(TYPE_SPEC type_spec, MccIdentifier *id = nullptr, int array_size = -1) {}
	virtual ~MccFuncParameter(void);

	TYPE_SPEC m_type_spec;
	MccIdentifier *m_name;
};

