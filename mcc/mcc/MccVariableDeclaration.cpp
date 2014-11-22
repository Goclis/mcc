#include "MccVariableDeclaration.h"


MccVariableDeclaration::MccVariableDeclaration(TYPE_SPEC type_spec, MccIdentifier *identifier, int array_size)
	: MccDeclaration(type_spec, identifier),
	  m_array_size(array_size)
{
}


MccVariableDeclaration::~MccVariableDeclaration(void)
{
}
