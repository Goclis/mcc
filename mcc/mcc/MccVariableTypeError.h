#pragma once
#include "mccsemanticerror.h"
#include <string>
using std::string;

/**
 * @brief Need to report following information:
 *	1. line number.
 *	2. identifier name.
 */
class MccVariableTypeError :
	public MccSemanticError
{
public:
	MccVariableTypeError(const string &id_name);
	virtual ~MccVariableTypeError(void);

	void report() const;

	string m_id_name;
};

