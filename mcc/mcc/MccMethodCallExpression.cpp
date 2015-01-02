#include "MccMethodCallExpression.h"
#include "MccExpressionList.h"
#include "MccIdentifier.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"


MccMethodCallExpression::MccMethodCallExpression(MccIdentifier *id, MccExpressionList *expr_list)
	: m_method_id(id)
{
	if (expr_list != nullptr) {
		expr_list->copy_to_list(this->m_args);
	}
}


MccMethodCallExpression::~MccMethodCallExpression(void)
{
	if (this->m_method_id != nullptr) {
		delete this->m_method_id;
	}

	for (size_t i = 0, len = this->m_args.size(); i < len; ++i) {
		if (this->m_args[i]) {
			delete this->m_args[i];
		}
	}
}


int MccMethodCallExpression::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	string func_name = this->m_method_id->m_name;
#ifdef DEBUG_MODE
	code_buffer += "MccMethodCallExpression generation.\n";
#endif

	// Push $fp.
	code_buffer += 
		"sw $t0, 0H($sp)\n"
		"addiu $v0, $zero, 1\n"
		"subu $sp, $sp, $v0\n";
	robot
		.add_code("sw $t0, 0H($sp)")
		.add_code("addiu $v0, $zero, 1")
		.add_code("subu $sp, $sp, $v0");

	int i = this->m_args.size() - 1;
	for (; i >= 0; --i) {
		this->m_args[i]->generate_code();

		// Push $v0.
		code_buffer += 
			"sw $v0, 0H($sp)\n"
			"addiu $v0, $zero, 1\n"
			"subu $sp, $sp, $v0\n";
		robot
			.add_code("sw $v0, 0H($sp)")
			.add_code("addiu $v0, $zero, 1")
			.add_code("subu $sp, $sp, $v0");
	}
	
	code_buffer +=
		"jal " + func_name + "\n"
		"srlv $v1, $zero, $zero\n";
	robot
		.add_code("jal " + func_name)
		.add_code("srlv $v1, $zero, $zero");

	return 0;
}


void MccMethodCallExpression::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
