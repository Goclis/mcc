#include "MccContinueStatement.h"
#include "MccRobot.h"

MccContinueStatement::MccContinueStatement()
{

}

MccContinueStatement::~MccContinueStatement()
{
	
}


int MccContinueStatement::generate_code() const
{
	// cout << "MccContinueStatement generation." << endl;
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	code_buffer += "jp " + robot.get_current_continue_label() + "\n";

	return 0;
}
