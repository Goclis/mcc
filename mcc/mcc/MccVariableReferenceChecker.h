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
class MccIfStatement;
class MccBlockStatement;
class MccReturnStatement;
class MccBinaryOperatorExpression;
class MccUnaryOperatorExpression;
class MccMethodCallExpression;
class MccIdentifier;

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
	void detect(MccIfStatement *if_stmt);
	void detect(MccReturnStatement *rtn_stmt);
	void detect(MccBinaryOperatorExpression *binary_expr);
	void detect(MccUnaryOperatorExpression *unary_expr);
	void detect(MccMethodCallExpression *mc_expr);
	void detect(MccIdentifier *ident);

	
	vector<string> m_global_var_name;
	vector<string> m_local_var_name;
	void *m_current_scope;
};

