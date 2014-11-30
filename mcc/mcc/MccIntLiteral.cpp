#include "MccIntLiteral.h"


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
	cout << "MccIntLiteral generation." << endl;

	cout << "li $a0 " << this->get_value() << endl;

	return 0;
}
