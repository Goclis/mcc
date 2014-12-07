#pragma once

#include <vector>

class MccVariableDeclaration;
class MccFunctionDeclaration;
class MccSemanticError;

using std::vector;

/**
 * @brief Base class of semantic error checker.
 */
class MccSemanticErrorChecker
{
public:
	MccSemanticErrorChecker(void);
	virtual ~MccSemanticErrorChecker(void);

	vector<MccSemanticError*>& get_error_list();

	virtual void detect(MccVariableDeclaration *var) {}
	virtual void detect(MccFunctionDeclaration *fun) {}
	
protected:
	vector<MccSemanticError*> m_error_list;
};

