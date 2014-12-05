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
	string &code_buffer = theMccRobot().get_code_buffer();
	code_buffer += "MccIntLiteral generation.\n";

	code_buffer 
		+= Utility::string_concat_int("addi $v0 $zero ", this->get_value()) + "\n";

	return 0;
}
