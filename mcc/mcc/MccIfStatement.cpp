#include "MccIfStatement.h"
#include "MccExpression.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"
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
#ifdef DEBUG_MODE
	code_buffer += "MccIfStatement generation.\n";
#endif
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();
	func_decl->increase_cond_stmt_level();
	string if_label = "if_";
	if_label += robot.generate_branch_label();
	string false_branch_label = if_label + "_false";
	string if_end = if_label + "_end";

	// Gen(m_condition).
	this->m_condition->generate_code();
	code_buffer += "beq $v0 0 " + false_branch_label + "\n";
	robot
		.add_code("beq $v0, 0, " + false_branch_label);

	// Gen(m_if).
	this->m_if->generate_code();
	code_buffer += 
		"j " + if_end + "\n";
	robot
		.add_code("j " + if_end);

	// Gen(m_else), if have.
	code_buffer += 
		false_branch_label + ":\n";
	robot
		.add_code(false_branch_label + ":");
	if (this->m_else != nullptr) {
		this->m_else->generate_code();
	}

	code_buffer += 
		if_end + ":\n";
	robot
		.add_code(if_end + ":");
	func_decl->decrease_cond_stmt_level();

	return 0;
}


void MccIfStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
