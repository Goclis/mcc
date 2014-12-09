#include "MccStatement.h"


MccStatement::MccStatement(void)
{
}


MccStatement::~MccStatement(void)
{
}


//@todo Remove it.
int MccStatement::generate_code() const
{
	cout << "MccStatement generation." << endl;

	return 0;
}

//@todo Remove it.
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
