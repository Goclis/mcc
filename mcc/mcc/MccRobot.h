/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccDeclarationList;
class MccDeclaration;

using std::vector;

/**
 * @brief Global robot, singleton.
 */
class MccRobot
{
public:
	virtual ~MccRobot(void);
	friend MccRobot& theMccRobot();
	
	/**
	 * @brief Use declaration list to initialize robot.
	 */
	void initialize(MccDeclarationList *decl_list);

private:
	MccRobot(void);
	vector<MccDeclaration *> m_decls;
};

