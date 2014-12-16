/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>
#include <string>
#include "MccPublicType.h"

class MccDeclarationList;
class MccDeclaration;
class MccIdentifier;
class MccFunctionDeclaration;
class MccSemanticErrorChecker;

using std::vector;
using std::string;

#define DEBUG_MODE 1

/**
 * @brief Global robot, singleton.
 */
class MccRobot
{
public:
	virtual ~MccRobot(void);

	/**
	 * @brief Singleton pattern, get the global robot.
	 */
	friend MccRobot& theMccRobot();
	
	/**
	 * @brief Use declaration list to initialize robot.
	 */
	void initialize(MccDeclarationList *decl_list);

	/**
	 * @brief Generate code.
	 */
	void generate_code();

	/**
	 * @brief Check semantic error.
	 *
	 * @return true means no error, false means error.
	 */
	bool check_semantic_error();

	/**
	 * @brief Add new declration.
	 *
	 * @param name The name of the declaration variable.
	 *
	 * @param decl_size The size of the declaration variable.
	 *		0 indicates function declaration,
	 *		1 indicates global normal variable,
	 *	    1+ indicates global array variable.
	 *
	 * @return The info struct of the declaration.
	 */
	IdentifierInfo* add_global_decl(const string &name, int decl_size);

	/**
	 * @brief Generate branch label for code generation.
	 *
	 * @return The label of the branch.
	 */
	string generate_branch_label();
	

	/**
	 * @brief Get the information of the global identifer.
	 *
	 * @param name The name of the identifer.
	 *
	 * @return If find return the information, otherwise, return null.
	 */
	IdentifierInfo* get_identifier_info(const string &name);

	/**
	 * @brief Setters and Getters.
	 */
	void set_current_break_label(const string &new_label);
	string get_current_break_label() const;
	void set_current_continue_label(const string &new_label);
	string get_current_continue_label() const;
	void set_current_func_decl(MccFunctionDeclaration *new_fun);
	MccFunctionDeclaration* get_current_func_decl() const;
	string& get_code_buffer();
	string& get_global_var_code_buffer();
	MccSemanticErrorChecker* get_current_checker() const;
	string get_global_fp() const;

private:
	MccRobot(void);

	/**
	 * @brief All declarations.
	 */
	vector<MccDeclaration *> m_decls;

	/**
	 * @brief Semantic error check states.
	 */
	MccSemanticErrorChecker *m_current_checker;

	/**
	 * @brief Code generation states.
	 */
	string m_current_break_label; // Current while statement end.
	string m_current_continue_label; // Current while statement start.
	MccFunctionDeclaration *m_current_func_decl; // Current function declaration.
	int m_branch_nums; // Salt for generating branch name.
	string m_global_fp; // Global $fp.
	int m_global_var_size; // The total size of all global variables.
	IdentifierMap m_decl_infos; // A map to save information for each declaration.

	/**
	 * @brief Buffers.
	 */
	string m_code_buffer; // Buffer for generated code.
	string m_global_var_code_buffer; // Buffer for global variable declaration.
};

