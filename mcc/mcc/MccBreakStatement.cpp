#include "MccBreakStatement.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"

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


void MccBreakStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
