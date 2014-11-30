#include "MccVariableDeclaration.h"
#include "MccIdentifier.h"


MccVariableDeclaration::MccVariableDeclaration(
		TYPE_SPEC type_spec, 
		MccIdentifier *identifier, 
		int array_size)
	: MccDeclaration(type_spec, identifier),
	  m_array_size(array_size)
{
}


MccVariableDeclaration::~MccVariableDeclaration(void)
{
	// Identifier released by base class destructor.
}


int MccVariableDeclaration::generate_code()
{
	cout << "MccVariableDeclaration generation." << endl;
	
	int stack_used = 4;
	
	bool is_array_variable = (this->m_array_size != -1);
	if (is_array_variable) {
		stack_used = 4 * this->m_array_size;
	}

	cout << "subiu $sp $sp " << stack_used << endl;

	return stack_used;
}
