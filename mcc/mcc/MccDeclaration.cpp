#include "MccDeclaration.h"
#include "MccIdentifier.h"


MccDeclaration::MccDeclaration(TYPE_SPEC type_spec, MccIdentifier *identifier)
	: m_type_spec(type_spec),
	  m_identifier(identifier)
{

}


MccDeclaration::~MccDeclaration(void)
{
	if (this->m_identifier) {
		delete this->m_identifier;
	}
}

//@todo Remove it.
int MccDeclaration::generate_code()
{
	// cout << "MccDeclaration generation." << endl;

	return 0;
}


string MccDeclaration::get_decl_name() const
{
	return this->m_identifier->m_name;
}


void MccDeclaration::semantic_detect()
{

}


TYPE_SPEC MccDeclaration::get_type_spec() const
{
	return m_type_spec;
}


void MccDeclaration::set_lineno(int lineno)
{
	m_lineno = lineno;
}

int MccDeclaration::get_lineno() const
{
	return m_lineno;
}
