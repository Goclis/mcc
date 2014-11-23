#include "MccRobot.h"
#include "MccDeclarationList.h"
#include "MccDeclaration.h"
#include <iostream>
using namespace std;

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
	// Release declarations.
	for (size_t i = 0, len = this->m_decls.size(); i < len; ++i) {
		delete this->m_decls[i];
	}
}


void MccRobot::initialize(MccDeclarationList *decl_list)
{
	cout << "Hello" << endl;
	if (decl_list != nullptr) {
		// copy to m_decls
		cout << "Not empty program" << endl;
		decl_list->copy_to_list(this->m_decls);
	}


}

