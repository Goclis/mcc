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
};
