/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"

/**
 * @brief Support continue statement.
 */
class MccContinueStatement :
	public MccStatement
{
public:
	MccContinueStatement(void);
	virtual ~MccContinueStatement(void);

	int generate_code() const;
	void semantic_detect();
};
