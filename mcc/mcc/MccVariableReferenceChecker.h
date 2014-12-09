#pragma once
#include "mccsemanticerrorchecker.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class MccVariableDeclaration;
class MccFunctionDeclaration;
class MccAssignStatement;
class MccWhileStatement;
class MccBlockStatement;

/**
 * @brief Check whether varaiables referenced exist.
 *
 * @need Must pass MccMethodParameterNameExistChecker.
 */
class MccVariableReferenceChecker :
	public MccSemanticErrorChecker
{
public:
	MccVariableReferenceChecker(void);
	virtual ~MccVariableReferenceChecker(void);

	void detect(MccVariableDeclaration *var);
	void detect(MccFunctionDeclaration *fun);
	void detect(MccAssignStatement *assign_stmt);
	void detect(MccWhileStatement *while_stmt);
	void detect(MccBlockStatement *block_stmt);

	
	vector<string> m_global_var_name;
	vector<string> m_local_var_name;
	void *m_current_scope;
};

