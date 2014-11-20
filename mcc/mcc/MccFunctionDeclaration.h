/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include "mccdeclaration.h"
#include <vector>

class MccVariableDeclaration;

using std::vector;

/**
 * @brief Function declaration class, include definition information.
 */
class MccFunctionDeclaration :
	public MccDeclaration
{
public:
	MccFunctionDeclaration(void);
	virtual ~MccFunctionDeclaration(void);

	/**
	 * @brief Add new local variable declaration.
	 *
	 * @param decl
	 */
	void add_local_decl(MccVariableDeclaration *decl);

private:
	/**
	 * @brief local variable declarations.
	 */
	vector<MccVariableDeclaration *> m_local_variable_decls;
	
	/**
	 * @brief function parameter list.
	 */
	// vector<MccFuncParameter *> m_parameter_list;

	/**
	 * @brief statement list.
	 */
	// vector<MccStatement *> m_statement_list;
};

