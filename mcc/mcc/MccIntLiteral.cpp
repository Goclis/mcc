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
