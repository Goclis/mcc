/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"

class MccBreakStatement :
	public MccStatement
{
public:
	MccBreakStatement(void);
	virtual ~MccBreakStatement(void);

	int generate_code() const;
	void semantic_detect();
};
