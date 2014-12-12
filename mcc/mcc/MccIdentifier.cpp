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
	
	// The 'info' should not be nullptr if passed semantic error check.
	if (nullptr == info) {
		exit(1);
	}

	if (nullptr == info->scope) {
		// Global variable.
		// The base $fp of global variables.
		string global_fp = "4000"; //@todo
		if (ARRAY_VAR == info->id_type) {
			code_buffer +=
				"addiu $v0 $zero " + global_fp + "\n"
				"addiu $v1 $zero " + info->position + "\n"
				"subu $v0 $v0 $v1\n";
		} else if (NOMARL_VAR == info->id_type) {
			code_buffer +=
				"addiu $v0 $zero " + global_fp + "\n"
				"sw $v0 (-" + info->position + ")$v0\n";
		}
	} else {
		// Local variable.
		if (ARRAY_VAR == info->id_type) {
			code_buffer += 
				"addiu $v1 $zero " + info->position + "\n"
				"subu $v0 $fp $v1\n";
		} else if (NOMARL_VAR == info->id_type) {
			code_buffer += "sw $v0 (-" + info->position + ")$fp\n";
		}
	}	

	return 0;
}


void MccIdentifier::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
