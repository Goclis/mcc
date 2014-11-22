#include "MccFunctionDeclaration.h"
#include "MccVariableDeclaration.h"


MccFunctionDeclaration::MccFunctionDeclaration(void)
{
}


MccFunctionDeclaration::~MccFunctionDeclaration(void)
{
	// Release all local variable declarations.
	for (size_t i = 0, len = this->m_local_variable_decls.size();
			i < len; ++i) {
		if (this->m_local_variable_decls[i]) {
			delete this->m_local_variable_decls[i];
		}
	}
}
