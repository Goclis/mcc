#include "MccBreakStatement.h"
#include "MccRobot.h"

MccBreakStatement::MccBreakStatement()
{

}

MccBreakStatement::~MccBreakStatement()
{
	
}


int MccBreakStatement::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	code_buffer += "MccBreakStatement generation.\n";

	code_buffer += "j " + robot.get_current_break_label() + "\n";

	return 0;
}
