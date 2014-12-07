#pragma once
#include "mccsemanticerrorchecker.h"

class MccVariableTypeChecker :
	public MccSemanticErrorChecker
{
public:
	MccVariableTypeChecker(void);
	virtual ~MccVariableTypeChecker(void);

	/**
	 * @brief Check the type of the variable, if the type if void,
	 *	add an MccVariableTypeError to list.
	 */
	void detect(MccVariableDeclaration *var);
	
	/**
	 * @brief Check the local variables of the function.
	 */
	void detect(MccFunctionDeclaration *fun);
};

