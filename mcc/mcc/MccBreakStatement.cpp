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
#ifdef DEBUG_MODE
	code_buffer += "MccBreakStatement generation.\n";
#endif

	code_buffer += "j " + robot.get_current_break_label() + "\n";

	robot
		.add_code("j " + robot.get_current_break_label())
		.add_code("srlv $v1, $zero, $zero");

	return 0;
}


void MccBreakStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
