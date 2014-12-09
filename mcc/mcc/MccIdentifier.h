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
	
	/**
	 * @brief Save the address of the identifier into the return register
	 *	for array variable. For normal variable, save the value.
	 */
	int generate_code() const;
	void semantic_detect();

	string m_name;
};

