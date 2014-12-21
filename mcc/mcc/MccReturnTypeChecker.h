#pragma once
#include "MccSemanticErrorChecker.h"
#include "MccPublicType.h"


class MccReturnTypeChecker :
	public MccSemanticErrorChecker
{
public:
	MccReturnTypeChecker();
	virtual ~MccReturnTypeChecker();

	/**
	 * @brief Set up the current return type for future check.
	 */
	void detect(MccFunctionDeclaration *fun);
	
	/**
	 * @brief Check whether the return type (if have) is compatible with
	 *	current function.
	 */
	void detect(MccReturnStatement *ret_stmt);


	TYPE_SPEC m_func_return_type;
};

