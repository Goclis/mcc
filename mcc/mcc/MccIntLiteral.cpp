#include "MccIntLiteral.h"
#include "MccRobot.h"
#include "Utility.h"


MccIntLiteral::MccIntLiteral(int value)
	: m_value(value)
{
	
}


MccIntLiteral::~MccIntLiteral(void)
{
}


int MccIntLiteral::get_value() const
{
	return this->m_value;
}


int MccIntLiteral::generate_code() const
{
	// cout << "MccIntLiteral generation." << endl;

	theMccRobot().get_code_buffer()
		+= Utility::string_concat_int("li $a0 ", this->get_value())
		+ "\n";

	return 0;
}
