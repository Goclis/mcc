#pragma once
#include "mccsemanticerrorchecker.h"

class MccFunctionDeclaration;

/**
 * @brief Check the name of method, `label + number` is invalid.
 */
class MccMethodNameChecker :
	public MccSemanticErrorChecker
{
public:
	MccMethodNameChecker(void);
	virtual ~MccMethodNameChecker(void);

	/**
	 * @brief Check the name of method.
	 */
	void detect(MccFunctionDeclaration *fun);
};

