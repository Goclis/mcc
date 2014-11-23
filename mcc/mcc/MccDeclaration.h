/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <string>
#include "MccPublicType.h"

class MccIdentifier;

using std::string;

/**
 * @brief Base class for declaration.
 */
class MccDeclaration
{
public:
	MccDeclaration(
		TYPE_SPEC type_spec,
		MccIdentifier *identifier);
	virtual ~MccDeclaration(void);

protected:
	MccIdentifier *m_identifier;
	TYPE_SPEC m_type_spec;
};

