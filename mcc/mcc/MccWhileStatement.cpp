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
	string while_start_label = robot.generate_while_label();
	string break_label = while_start_label + "end";

	// Backup for later recovery.
	string continue_label_bak = robot.get_current_continue_label();
	string break_label_bak = robot.get_current_break_label();

	// Set up new label.
	robot.set_current_break_label(break_label);
	robot.set_current_continue_label(while_start_label);

	cout << "MccWhileStatement generation." << endl;
	cout << while_start_label << ":" << endl;
	this->m_condition->generate_code();
	cout << "beq $a0 0 " << break_label << endl;
	this->m_statement->generate_code();
	cout << break_label << ":" << endl;

	// Recovery.
	robot.set_current_break_label(break_label_bak);
	robot.set_current_continue_label(continue_label_bak);

	return 0;
}
