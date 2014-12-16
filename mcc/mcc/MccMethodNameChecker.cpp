#include "MccMethodNameChecker.h"
#include "MccInvalidMethodNameError.h"
#include "MccFunctionDeclaration.h"
#include "MccRobot.h"


MccMethodNameChecker::MccMethodNameChecker(void)
{
}


MccMethodNameChecker::~MccMethodNameChecker(void)
{
}


void MccMethodNameChecker::detect(MccFunctionDeclaration *fun)
{
	string func_name = fun->get_decl_name();
	int pos = func_name.find("label");
	if (pos == 0) {
		for (int i = 5, len = func_name.length(); i < len; ++i) {
			if (func_name[i] <= '0' || func_name[i] >= '9') {
				return;
			}
		}
		MccInvalidMethodNameError *error = new MccInvalidMethodNameError(func_name);
		error->m_line_no = fun->get_lineno();
		m_error_list.push_back(error);
	}
}
