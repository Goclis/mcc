/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <iostream>

using std::cout;
using std::endl;

class MccStatement
{
public:
	MccStatement(void);
	virtual ~MccStatement(void);

	/**
	 * @brief Generate code for this statement.
	 *
	 * @return If the statement push elements into stack when generates code,
	 *	return the stack space it used, otherwise return 0.
	 */
	virtual int generate_code() const;
	virtual void semantic_detect();
	
	int get_lineno() const;
	void set_lineno(int lineno);
protected:
	int m_lineno;
};

