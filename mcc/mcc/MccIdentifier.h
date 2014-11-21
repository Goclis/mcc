/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"
#include <string>

using std::string;

class MccIdentifier :
	public MccExpression
{
public:
	MccIdentifier(void);
	virtual ~MccIdentifier(void);

	string m_name;
};

