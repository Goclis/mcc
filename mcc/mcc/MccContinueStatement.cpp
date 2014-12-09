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
	code_buffer += "MccContinueStatement generation.\n";

	code_buffer += "j " + robot.get_current_continue_label() + "\n";

	return 0;
}


void MccContinueStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
