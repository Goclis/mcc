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
	virtual ~MccDeclarationList(void);

	vector<MccDeclaration *> m_decl_list;
};

