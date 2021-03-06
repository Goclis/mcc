#include "MccVariableTypeChecker.h"
#include "MccVariableTypeError.h"
#include "MccVariableDeclaration.h"
#include "MccFunctionDeclaration.h"


MccVariableTypeChecker::MccVariableTypeChecker(void)
{
}


MccVariableTypeChecker::~MccVariableTypeChecker(void)
{
}


void MccVariableTypeChecker::detect(MccVariableDeclaration *var)
{
	if (VOID_TYPE_SPEC == var->get_type_spec()) {
		MccVariableTypeError *error = new MccVariableTypeError(var->get_decl_name());
		error->m_lineno = var->get_lineno();
		m_error_list.push_back(error);
	}
}


void MccVariableTypeChecker::detect(MccFunctionDeclaration *fun)
{
	const vector<MccVariableDeclaration*> &decls = fun->get_local_variable_decls();
	for (size_t i = 0; i < decls.size(); ++i) {
		decls[i]->semantic_detect();
	}
}
