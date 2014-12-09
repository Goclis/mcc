#pragma once

#include <vector>

class MccFuncParameter;
class MccVariableDeclaration;
class MccFunctionDeclaration;
class MccWhileStatement;
class MccIfStatement;
class MccBlockStatement;
class MccBreakStatement;
class MccContinueStatement;
class MccAssignStatement;
class MccReturnStatement;
class MccBinaryOperatorExpression;
class MccUnaryOperatorExpression;
class MccMethodCallExpression;
class MccIdentifier;
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
	
	virtual void detect(MccFuncParameter *func_param) {}
	virtual void detect(MccVariableDeclaration *var) {}
	virtual void detect(MccFunctionDeclaration *fun) {}
	virtual void detect(MccWhileStatement *while_stmt) {}
	virtual void detect(MccIfStatement *if_stmt) {}
	virtual void detect(MccBlockStatement *block_stmt) {}
	virtual void detect(MccBreakStatement *brk_stmt) {}
	virtual void detect(MccContinueStatement *ctn_stmt) {}
	virtual void detect(MccAssignStatement *assign_stmt) {}
	virtual void detect(MccReturnStatement *rtn_stmt) {}
	virtual void detect(MccBinaryOperatorExpression *binary_expr) {}
	virtual void detect(MccUnaryOperatorExpression *unary_expr) {}	
	virtual void detect(MccMethodCallExpression *mc_expr) {}
	virtual void detect(MccIdentifier *ident) {}

	
protected:
	vector<MccSemanticError*> m_error_list;
};

