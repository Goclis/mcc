/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccDeclaration;

using std::vector;

class MccDeclarationList
{
public:
	MccDeclarationList(void);
	MccDeclarationList(MccDeclaration *first) {}
	virtual ~MccDeclarationList(void);

	void push_back(MccDeclaration *decl) {}

	vector<MccDeclaration *> m_decl_list;
};

