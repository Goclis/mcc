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

	/**
	 * @brief Same as vector::push_back.
	 */
	void push_back(MccStatement *stmt);

	/**
	 * @brief Copy content to other list.
	 *
	 * @param list Destination list.
     */
	void copy_to_list(vector<MccStatement *> &list); 

private:
	vector<MccStatement *> m_stmt_list;
};

