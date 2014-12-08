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
class IdentifierInfo;

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

	int generate_code();

	void semantic_detect();

	/**
	 * @brief Add a new variable declaration (locally).
	 *
	 *	This method doesn't do any check for conflict. Before call this
	 *	method, do check for exsitent conflict.
	 *
	 * @param name the name of the variable.
	 *
	 * @param var_size the size of the variable.
	 */
	void add_local_var_decl(const string &name, int var_size);

	/**
	 * @brief Get the information of the local identifer in function.
	 *
	 * @param name the name of the identifer.
	 *
	 * @return if find return the information, otherwise, return null.
	 */
	IdentifierInfo* get_identifier_info(const string &name);
	
	/**
	 * @brief Search the information of the identifier, from local to global.
	 *
	 * @param name the name of the identifier.
	 *
	 * @return if find return the information, otherwise, return null.
	 */
	IdentifierInfo* search_identifier_info(const string &name);

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
	int get_cond_stmt_level() const;
	void increase_cond_stmt_level();
	void decrease_cond_stmt_level();
	void set_has_retrieved();
	int get_ar_size() const;
	int get_vars_size() const;
	const vector<MccVariableDeclaration*>& get_local_variable_decls();
	bool is_definition() const;
	const vector<MccFuncParameter*>& get_parameter_list();

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
	 * @brief To figure out that this is a declaration or a definition.
	 */
	bool m_contain_definition;

	/**
	 * @brief When enter a condition statement block, increase by 1,
	 *	When exit a condition statement block, decrease by 1.
	 *
	 *	Condtion statements include if and while.
	 */
	int m_condition_block_levels;
	
	/**
	 * @brief Indicate whether the declaration has generated code to
	 *	retrieve the space of activation record.
	 *
	 *	A return statement may set this value to true.
	 */
	bool m_has_retrieved;
	
	/**
	 * @brief The value is the size of local variables.
	 */
	int m_local_var_size;

	/**
	 * @brief The value is the size of activation record.
	 *	
	 *	Include $fp, arguments and local variables.
	 */
	int m_ar_size;

	/**
	 * @brief A map to save the information of local variable definitions.
	 */
	IdentifierMap m_local_identifiers;
};

