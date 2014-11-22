/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include "MccDeclaration.h"

class MccIdentifier;

/**
 * @brief Variable declaration class.
 */
class MccVariableDeclaration :
	public MccDeclaration
{
public:
	MccVariableDeclaration(TYPE_SPEC type_spec, MccIdentifier *identifier, int array_size = -1);
	virtual ~MccVariableDeclaration(void);

private:
	/**
	 * @brief -1 indicates normal variable,
	 *		non-negative indicates array variable.
	 */
	int m_array_size;
};

