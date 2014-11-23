/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include "mccdeclaration.h"
#include <vector>

class MccVariableDeclaration;
class MccFuncParameter;
class MccStatement;
class MccStatementList;
class MccDeclarationList;
class MccFuncParameterList;

using std::vector;

/**
 * @brief Function declaration class, include definition information.
 */
class MccFunctionDeclaration :
	public MccDeclaration
{
public:
	MccFunctionDeclaration(
		TYPE_SPEC type_spec, 
		MccIdentifier *identifier, 
		MccFuncParameterList *params, 
		MccDeclarationList *decls = nullptr,
		MccStatementList *stmts = nullptr);
	virtual ~MccFunctionDeclaration(void);

private:
	/**
	 * @brief Local variable declarations.
	 */
	vector<MccVariableDeclaration *> m_local_variable_decls;
	
	/**
	 * @brief Function parameter list.
	 */
	vector<MccFuncParameter *> m_parameter_list;

	/**
	 * @brief Statement list.
	 */
	vector<MccStatement *> m_statement_list;

	/**
	 * @brief Indicate that whether the declaration contains definition or not;
	 */
	bool m_contain_definition;
};

