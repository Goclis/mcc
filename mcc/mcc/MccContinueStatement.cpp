#include "MccContinueStatement.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"

MccContinueStatement::MccContinueStatement()
{

}

MccContinueStatement::~MccContinueStatement()
{
	
}


int MccContinueStatement::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccContinueStatement generation.\n";
#endif

	code_buffer +=
		"j " + robot.get_current_continue_label() + "\n"
		"srlv $v1, $zero, $zero\n";

	robot
		.add_code("j " + robot.get_current_continue_label())
		.add_code("srlv $v1, $zero, $zero");

	return 0;
}


void MccContinueStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
