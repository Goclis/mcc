/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccstatement.h"
#include "MccStatementList.h"
#include <vector>

using std::vector;

class MccBlockStatement :
	public MccStatement
{
public:
	MccBlockStatement(MccStatementList *stmt_list);
	virtual ~MccBlockStatement(void);

private:
	vector<MccStatement *> m_statement_list;		
};

