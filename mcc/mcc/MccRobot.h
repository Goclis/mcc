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

using std::vector;
using std::string;

/**
 * @brief Global robot, singleton.
 */
class MccRobot
{
public:
	virtual ~MccRobot(void);
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
	 * @brief Add new declration.
	 *
	 * @param name the name of the declaration variable.
	 *
	 * @param decl_size the size of the declaration variable.
	 *		0 indicates function declaration,
	 *		4 indicates global normal variable,
	 *	    4+ indicates global array variable.
	 *
	 * @return The info struct of the declaration.
	 */
	IdentifierInfo* add_global_decl(const string &name, int decl_size);

	/**
	 * @brief Generate false branch label for if statement.
	 *
	 * @return The label of the branch.
	 */
	string generate_false_branch_label();

	/**
	 * @brief Setters and Getters.
	 */
	void set_current_break_label(const string &new_label);
	string get_current_break_label() const;
	void set_current_continue_label(const string &new_label);
	string get_current_continue_label() const;
	void set_current_func_decl(MccFunctionDeclaration *new_fun);
	MccFunctionDeclaration* get_current_func_decl() const;

private:
	MccRobot(void);
	vector<MccDeclaration *> m_decls;

	/**
	 * @brief Code generation states.
	 */
	string m_current_break_label; // Current while statement end.
	string m_current_continue_label; // Current while statement start.
	MccFunctionDeclaration *m_current_func_decl; // Current function declaration.
	int m_false_branch_nums;
	
	/**
	 * @brief A map to save information for each declaration.
	 */
	IdentifierMap m_decl_infos;
};

