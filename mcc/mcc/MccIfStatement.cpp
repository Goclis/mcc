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
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	code_buffer += "MccIfStatement generation.\n";
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();
	func_decl->increase_cond_stmt_level();
	string false_branch_label = robot.generate_false_branch_label();
	string false_branch_end = false_branch_label + "_end";
	this->m_condition->generate_code();
	code_buffer += "beq $v0 0 " + false_branch_label + "\n";
	this->m_if->generate_code();
	code_buffer += "j " + false_branch_end + "\n";
	code_buffer += false_branch_label + ":\n";
	if (this->m_else != nullptr) {
		this->m_else->generate_code();
	}
	code_buffer += false_branch_end + ":\n";
	func_decl->decrease_cond_stmt_level();

	return 0;
}
