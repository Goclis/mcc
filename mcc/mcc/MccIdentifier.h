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
	explicit MccIdentifier(string *str);
	virtual ~MccIdentifier(void);

	string m_name;
};

