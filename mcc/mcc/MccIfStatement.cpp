#include "MccIfStatement.h"
#include "MccExpression.h"
#include "MccRobot.h"
#include "MccFunctionDeclaration.h"
#include <string>

using std::string;


MccIfStatement::MccIfStatement(
		MccExpression *condition, 
		MccStatement *if_part, 
		MccStatement *else_part)
	: MccConditionStatement(condition),
	  m_if(if_part),
	  m_else(else_part)
{
}


MccIfStatement::~MccIfStatement(void)
{
	if (this->m_if != nullptr) {
		delete this->m_if;
	}

	if (this->m_else != nullptr) {
		delete this->m_else;
	}
}


int MccIfStatement::generate_code() const
{
	cout << "MccIfStatement generation." << endl;
	MccRobot &robot = theMccRobot();
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();
	func_decl->increase_cond_stmt_level();
	string false_branch_label = robot.generate_false_branch_label();
	this->m_condition->generate_code();
	cout << "beq $a0 0 " << false_branch_label << endl; 
	this->m_if->generate_code();
	cout << false_branch_label << ":" << endl;
	if (this->m_else != nullptr) {
		this->m_else->generate_code();
	}
	func_decl->decrease_cond_stmt_level();
	return 0;
}
