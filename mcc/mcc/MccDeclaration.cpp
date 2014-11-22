#include "MccDeclaration.h"


MccDeclaration::MccDeclaration(std::string identifier_name, TYPE_SPEC type_spec)
	: m_identifier_name(identifier_name),
	  m_type_spec(type_spec)
{

}


MccDeclaration::~MccDeclaration(void)
{
}
