#include "MccIdentifier.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"
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
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	code_buffer += "MccIdentifier generation.\n";
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();
	IdentifierInfo *info = nullptr;
	if (nullptr == func_decl) {
		info = robot.get_identifier_info(this->m_name);
	} else {
		info = func_decl->search_identifier_info(this->m_name);
	}
	
	if (ARRAY_VAR == info->id_type) {
		code_buffer += "addi $v0 $fp -" + info->position + "\n";
	} else if (NOMARL_VAR == info->id_type) {
		code_buffer += "sw $v0 (-" + info->position + ")$fp\n";
	}

	return 0;
}


void MccIdentifier::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
