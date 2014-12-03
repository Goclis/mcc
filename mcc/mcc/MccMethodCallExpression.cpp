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
	string func_name = this->m_method_id->m_name;

	cout << "MccMethodCallExpression generation." << endl;
	cout << "sw $fp 0($sp)" << endl;
	cout << "addiu $sp $sp -4" << endl;

	int i = this->m_args.size() - 1;
	for (; i >= 0; --i) {
		this->m_args[i]->generate_code();
		cout << "sw $a0 0($sp)" << endl;
		cout << "addiu $sp $sp -4" << endl;
	}
	
	cout << "jal " << func_name << endl;

	return 0;
}
