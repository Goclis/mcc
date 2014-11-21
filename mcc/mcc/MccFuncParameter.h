/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include "MccDeclaration.h"

class MccIdentifier;

class MccFuncParameter
{
public:
	MccFuncParameter(void);
	virtual ~MccFuncParameter(void);

	MccDeclaration::TYPE_SPEC m_type_spec;
	MccIdentifier *m_name;	
};

