/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccDeclaration;
class MccVariableDeclaration;

using std::vector;

class MccDeclarationList
{
public:
	MccDeclarationList(MccDeclaration *first);
	virtual ~MccDeclarationList(void);

	/**
	 * @brief Same as vector::push_back.
	 */
	void push_back(MccDeclaration *decl);
	
	/**
	 * @brief Copy content to other list.
	 *
	 * @param list Destination list.
     */
	void copy_to_list(vector<MccDeclaration *> &list);
	
	/**
	 * @brief Similar to copy_to_list_base, but convert to MccVariableDeclaration.
	 *
	 * @param list Destination list.
     */
	void copy_to_list_derived(vector<MccVariableDeclaration *> &list);

private:
	vector<MccDeclaration *> m_decl_list;
};

