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
	// cout << "MccBreakStatement generation." << endl;
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	code_buffer += "jp " + robot.get_current_break_label() + "\n";

	return 0;
}
