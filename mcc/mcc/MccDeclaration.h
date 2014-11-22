/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <string>
#include "MccPublicType.h"

using std::string;

/**
 * @brief Base class for declaration.
 */
class MccDeclaration
{
public:
	MccDeclaration(
		string identifier_name = "",
		TYPE_SPEC type_spec = VOID_TYPE_SPEC);
	virtual ~MccDeclaration(void);

private:
	string m_identifier_name;
	TYPE_SPEC m_type_spec;
};

