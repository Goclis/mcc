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
	cout << "MccContinueStatement generation." << endl;

	cout << "jp " << theMccRobot().get_current_continue_label() << endl;

	return 0;
}
