#include "MccIdentifier.h"
#include "MccRobot.h"
#include "MccFunctionDeclaration.h"


MccIdentifier::MccIdentifier(void)
	: m_name("")
{
}


MccIdentifier::MccIdentifier(string *str)
	: m_name(*str)
{
	
}


MccIdentifier::~MccIdentifier(void)
{
}


int MccIdentifier::generate_code() const
{
	// cout << "MccIdentifier generation." << endl;
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();
	IdentifierInfo *info = nullptr;
	if (nullptr == func_decl) {
		info = robot.get_identifier_info(this->m_name);
	} else {
		info = func_decl->search_identifier_info(this->m_name);
	}
	
	if (info->id_type == NOMARL_VAR || info->id_type == ARRAY_VAR) {
		code_buffer += "lw $a0 " + info->position + "\n";
	}

	return 0;
}
