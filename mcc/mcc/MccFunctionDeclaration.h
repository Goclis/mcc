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
class MccReturnStatement;

using std::vector;

/**
 * @brief Function declaration class, include definition information.
 */
class MccFunctionDeclaration :
	public MccDeclaration
{
public:
	friend class MccReturnStatement;

	MccFunctionDeclaration(
		TYPE_SPEC type_spec, 
		MccIdentifier *identifier, 
		MccFuncParameterList *params, 
		MccDeclarationList *decls = nullptr,
		MccStatementList *stmts = nullptr);
	virtual ~MccFunctionDeclaration(void);

	int generate_code();

	/**
	 * @brief Setters and Getters.
	 *
	 * @todo FunctionDeclaration needs to offer several functions for these 
	 *	statements within it to report message.
	 *
	 *	For example, (1) MccVariableDeclaration needs to report a new variable name
	 *	and its size. (2) MccConditionStatement needs to report the change of current
	 *	block level. (3) MccReturnStatement needs to report whether the func should
	 *	generate code for retrieving activation record or not.
	 */
	int get_if_levels() const;
	void increase_if_level();
	void decrease_if_level();
	void set_has_retrieved();
	int get_ar_size() const;

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

	/**
	 * @brief A number to indicate the current of if statement(s).
	 *	
	 *	0 means there is no if statement.
	 *	1 means there is an if statement.
	 *	1+ means there are nested if statements.
	 */
	int m_if_levels;
	
	/**
	 * @brief Indicate whether the declaration has generated code to
	 *	retrieve the space of activation record.
	 *
	 *	A return statement may set this value to true.
	 */
	bool m_has_retrieved;

	/**
	 * @brief The value is the size of activation record.
	 *	
	 *	Include $fp, arguments and local variables.
	 */
	int m_ar_size;
};

