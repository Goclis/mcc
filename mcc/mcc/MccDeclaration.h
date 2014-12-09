/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <string>
#include <iostream>
#include "MccPublicType.h"

class MccIdentifier;

using std::string;
using std::cout;
using std::endl;

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

	/**
	 * @brief Generate code for this declaration.
	 *
	 * @return If the declaration push elements into stack when generates code, 
	 *	return the stack space it used, otherwise return 0.
	 */
	virtual int generate_code();
	virtual void semantic_detect();

	string get_decl_name() const;
	TYPE_SPEC get_type_spec() const;
	void set_lineno(int lineno);
	int get_lineno() const;

protected:
	MccIdentifier *m_identifier;
	TYPE_SPEC m_type_spec;
	int m_lineno;
};

