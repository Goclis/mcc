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
	MccFuncParameter(
		TYPE_SPEC type_spec, 
		MccIdentifier *id = nullptr, 
		int array_size = -1);
	virtual ~MccFuncParameter(void);

	void semantic_detect();

	void set_lineno(int lineno);
	int get_lineno() const;

	/**
	 * @brief Parameter format:
	 *	m_type_spec m_name [m_array_size].
	 */
	TYPE_SPEC m_type_spec;
	MccIdentifier *m_name;
	int m_array_size;

	int m_lineno;
};

