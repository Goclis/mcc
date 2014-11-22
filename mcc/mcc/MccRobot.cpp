#include "MccRobot.h"

MccRobot& theMccRobot()
{
	static MccRobot robot;
	return robot;
}


MccRobot::MccRobot(void)
{
}


MccRobot::~MccRobot(void)
{
}


void MccRobot::initialize(MccDeclarationList *decl_list)
{
	if (decl_list != nullptr) {
		// copy to m_decls
	}
}

