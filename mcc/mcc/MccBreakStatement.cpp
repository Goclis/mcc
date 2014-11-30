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
	cout << "MccBreakStatement generation." << endl;

	cout << "jp " << theMccRobot().get_current_break_label() << endl;

	return 0;
}
