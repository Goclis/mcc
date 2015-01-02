#include "MccStatement.h"


MccStatement::MccStatement(void)
{
}


MccStatement::~MccStatement(void)
{
}


int MccStatement::generate_code() const
{
	cout << "MccStatement generation." << endl;

	return 0;
}


void MccStatement::semantic_detect()
{

}


int MccStatement::get_lineno() const
{
	return m_lineno;
}

void MccStatement::set_lineno(int lineno)
{
	m_lineno = lineno;
}
