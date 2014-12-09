#pragma once

#include <vector>

class MccVariableDeclaration;
class MccFunctionDeclaration;
class MccWhileStatement;
class MccBlockStatement;
class MccBreakStatement;
class MccContinueStatement;
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
	virtual void detect(MccWhileStatement *while_stmt) {}
	virtual void detect(MccBlockStatement *block_stmt) {}
	virtual void detect(MccBreakStatement *brk_stmt) {}
	virtual void detect(MccContinueStatement *ctn_stmt) {}
	
protected:
	vector<MccSemanticError*> m_error_list;
};

