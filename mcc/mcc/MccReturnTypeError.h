#pragma once
#include "MccSemanticError.h"
#include "MccPublicType.h"

/**
 * @report
 *	1. line number of the return statement.
 *	2. function return type.
 *	3. return type of return statement.
 */
class MccReturnTypeError :
	public MccSemanticError
{
public:
	MccReturnTypeError();
	virtual ~MccReturnTypeError();

	void report() const;

	int m_line_no;
	TYPE_SPEC m_func_type;
	TYPE_SPEC m_ret_type;
};

