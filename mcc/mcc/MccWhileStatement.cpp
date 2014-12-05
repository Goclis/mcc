#include "MccWhileStatement.h"
#include "MccRobot.h"
#include "MccExpression.h"


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

	code_buffer += "MccWhileStatement generation.\n";
	code_buffer += while_start_label + ":\n";
	this->m_condition->generate_code();
	code_buffer += "beq $v0 0 " + break_label + "\n";
	this->m_statement->generate_code();
	code_buffer += break_label + ":\n";

	// Recovery.
	robot.set_current_break_label(break_label_bak);
	robot.set_current_continue_label(continue_label_bak);

	return 0;
}
