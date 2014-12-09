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

	int generate_code() const;
	void semantic_detect();

	const vector<MccStatement*>& get_statement_list();

private:
	vector<MccStatement *> m_statement_list;
};

