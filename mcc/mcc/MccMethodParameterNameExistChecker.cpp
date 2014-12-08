#include "MccMethodParameterNameExistChecker.h"
#include "MccMethodDefinitionLackParameterNameError.h"
#include "MccFunctionDeclaration.h"
#include "MccFuncParameter.h"


MccMethodParameterNameExistChecker::MccMethodParameterNameExistChecker(void)
{
}


MccMethodParameterNameExistChecker::~MccMethodParameterNameExistChecker(void)
{
}


void MccMethodParameterNameExistChecker::detect(MccFunctionDeclaration *fun)
{
	if (fun->is_definition()) {
		const vector<MccFuncParameter*> &parameter_list = fun->get_parameter_list();
		string fun_name = fun->get_decl_name();
		for (size_t i = 0, len = parameter_list.size(); i < len; ++i) {
			if (nullptr == parameter_list[i]->m_name) {
				m_error_list.push_back(new MccMethodDefinitionLackParameterNameError(
					fun_name, i + 1));
			}
		}
	}
}
