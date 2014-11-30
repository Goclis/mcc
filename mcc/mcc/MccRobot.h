/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>
#include <string>

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
	void generate_code() const;

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
};

