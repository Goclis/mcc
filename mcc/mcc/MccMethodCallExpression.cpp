#include "MccMethodCallExpression.h"
#include "MccExpressionList.h"
#include "MccIdentifier.h"
#include "MccRobot.h"


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

	code_buffer += "MccMethodCallExpression generation.\n";

	// Push $fp.
	code_buffer += "sw $fp 0($sp)\n";
	code_buffer += "subiu $sp $sp 4\n";

	int i = this->m_args.size() - 1;
	for (; i >= 0; --i) {
		this->m_args[i]->generate_code();

		// Push $v0.
		code_buffer += "sw $v0 0($sp)\n";
		code_buffer += "subiu $sp $sp 4\n";
	}
	
	code_buffer += "jal " + func_name + "\n";

	return 0;
}
