#include "MccWhileStatement.h"
#include "MccRobot.h"
#include "MccExpression.h"
#include "MccSemanticErrorChecker.h"


MccWhileStatement::MccWhileStatement(MccExpression *condition, MccStatement *stmt)
	: MccConditionStatement(condition),
	  m_statement(stmt)
{
}


MccWhileStatement::~MccWhileStatement(void)
{
	if (this->m_statement != nullptr) {
		delete this->m_statement;
	}
}


int MccWhileStatement::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	string while_start_label = "while_";
	while_start_label += robot.generate_branch_label();
	string break_label = while_start_label + "_end";

	// Backup for later recovery.
	string continue_label_bak = robot.get_current_continue_label();
	string break_label_bak = robot.get_current_break_label();

	// Set up new label.
	robot.set_current_break_label(break_label);
	robot.set_current_continue_label(while_start_label);

#ifdef DEBUG_MODE
	code_buffer += "MccWhileStatement generation.\n";
#endif
	code_buffer += 
		while_start_label + ":\n";
	robot
		.add_code(while_start_label + ":");

	// While condition.
	this->m_condition->generate_code();
	code_buffer +=
		"beq $v0, $zero, " + break_label + "\n"
		"srlv $v1, $zero, $zero\n";
	robot
		.add_code("beq $v0, $zero, " + break_label)
		.add_code("srlv $v1, $zero, $zero");

	// While body.
	this->m_statement->generate_code();

	// Jump back to the beginning of the while.
	code_buffer +=
		"j " + while_start_label + "\n"
		"srlv $v1, $zero, $zero\n";
	robot
		.add_code("j " + while_start_label)
		.add_code("srlv $v1, $zero, $zero");

	// While end.
	code_buffer += 
		break_label + ":\n";
	robot
		.add_code(break_label + ":");

	// Recovery.
	robot.set_current_break_label(break_label_bak);
	robot.set_current_continue_label(continue_label_bak);

	return 0;
}


void MccWhileStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
