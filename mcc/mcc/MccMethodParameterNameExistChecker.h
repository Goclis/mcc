#pragma once
#include "mccsemanticerrorchecker.h"

class MccFunctionDeclaration;

/**
 * @brief Check whether the parameter contains parameter name
 *	in the function definition.
 */
class MccMethodParameterNameExistChecker :
	public MccSemanticErrorChecker
{
public:
	MccMethodParameterNameExistChecker(void);
	virtual ~MccMethodParameterNameExistChecker(void);

	void detect(MccFunctionDeclaration *fun);
};

