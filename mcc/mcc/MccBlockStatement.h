/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"
#include <vector>

using std::vector;

class MccBlockStatement :
	public MccStatement
{
public:
	MccBlockStatement(void);
	virtual ~MccBlockStatement(void);

private:
	vector<MccStatement *> m_statement_list;		
};

