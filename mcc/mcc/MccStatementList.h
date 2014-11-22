/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccStatement;

using std::vector;

class MccStatementList
{
public:
	MccStatementList(MccStatement *first);
	virtual ~MccStatementList(void);

	void push_back(MccStatement *expr) {}

	vector<MccStatement *> m_stmt_list;
};

