/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <string>
using std::string;

/**
 * @brief Base class for declaration.
 */
class MccDeclaration
{
public:
	enum TYPE_SPEC {
		VOID_TYPE_SPEC, 
		INT_TYPE_SPEC
	};

	MccDeclaration(
		string identifier_name = "",
		TYPE_SPEC type_spec = VOID_TYPE_SPEC);
	virtual ~MccDeclaration(void);

private:
	string m_identifier_name;
	TYPE_SPEC m_type_spec;
};

