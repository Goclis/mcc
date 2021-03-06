#include "MccIdentifier.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"
#include "MccFunctionDeclaration.h"
#include "Utility.h"


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
#ifdef DEBUG_MODE
	code_buffer += "MccIdentifier generation.\n";
#endif
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
		string global_fp = robot.get_global_fp();
		if (ARRAY_VAR == info->id_type) {
			code_buffer +=
				"addiu $v0, $zero, " + global_fp + "\n" +
				Utility::string_concat_int("addiu $v1, $zero, ", info->position) + "\n"
				"subu $v0, $v0, $v1\n";
			robot
				.add_code("addiu $v0, $zero, " + global_fp)
				.add_code(Utility::string_concat_int("addiu $v1, $zero, ", info->position))
				.add_code("subu $v0, $v0, $v1");
		} else if (NOMARL_VAR == info->id_type) {
			code_buffer +=
				"addiu $v0, $zero, " + global_fp + "\n" +
				Utility::string_concat_int("addiu $v1, $zero, ", info->position) + "\n"
				"subu $v0, $v0, $v1\n"
				"lw $v0, 0H($v0)\n";
			robot
				.add_code("addiu $v0, $zero, " + global_fp)
				.add_code(Utility::string_concat_int("addiu $v1, $zero, ", info->position))
				.add_code("subu $v0, $v0, $v1")
				.add_code("lw $v0, 0H($v0)");
		}
	} else {
		// Local variable.
		if (ARRAY_VAR == info->id_type) {
			code_buffer += 
				Utility::string_concat_int("addiu $v0, $zero, ", info->position) + "\n"
				"subu $v0, $t0, $v0\n";
			robot
				.add_code(Utility::string_concat_int("addiu $v0, $zero, ", info->position))
				.add_code("subu $v0, $t0, $v0");
		} else if (NOMARL_VAR == info->id_type) {
			code_buffer +=
				Utility::string_concat_int("addiu $v0, $zero, ", info->position) + "\n"
				"subu $v0, $t0, $v0\n"
				"lw $v0, 0H($v0)\n";
			robot
				.add_code(Utility::string_concat_int("addiu $v0, $zero, ", info->position))
				.add_code("subu $v0, $t0, $v0")
				.add_code("lw $v0, 0H($v0)");
		} else if (PARAMETER_VAR == info->id_type) {
			code_buffer +=
				Utility::string_concat_int("addiu $v0, $zero, ", info->position) + "\n"
				"addu $v0, $t0, $v0\n"
				"lw $v0, 0H($v0)\n";
			robot
				.add_code(Utility::string_concat_int("addiu $v0, $zero, ", info->position))
				.add_code("addu $v0, $t0, $v0")
				.add_code("lw $v0, 0H($v0)");
		}
	}

	return 0;
}


void MccIdentifier::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
