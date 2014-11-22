/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccDeclarationList;
class MccDeclaration;

using std::vector;

class MccRobot
{
public:
	virtual ~MccRobot(void);
	friend MccRobot& theMccRobot();

	void initialize(MccDeclarationList *decl_list);

private:
	MccRobot(void);
	vector<MccDeclaration *> m_decls;
};

