#include "MccSemanticErrorChecker.h"
#include "MccSemanticError.h"


MccSemanticErrorChecker::MccSemanticErrorChecker(void)
{
}


MccSemanticErrorChecker::~MccSemanticErrorChecker(void)
{
	for (size_t i = 0; i < m_error_list.size(); ++i) {
		delete m_error_list[i];
	}
}


vector<MccSemanticError*>& MccSemanticErrorChecker::get_error_list()
{
	return m_error_list;
}