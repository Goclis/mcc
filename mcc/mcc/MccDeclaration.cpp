#include "MccDeclaration.h"


MccDeclaration::MccDeclaration(TYPE_SPEC type_spec, MccIdentifier *identifier)
	: m_type_spec(type_spec),
	  m_identifier(identifier)
{

}


MccDeclaration::~MccDeclaration(void)
{
}
