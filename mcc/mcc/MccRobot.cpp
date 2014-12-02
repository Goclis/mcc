#include "MccRobot.h"
#include "MccDeclarationList.h"
#include "MccDeclaration.h"
#include "Utility.h"
#include <iostream>
using namespace std;

MccRobot& theMccRobot()
{
	static MccRobot robot;
	return robot;
}


MccRobot::MccRobot(void)
{
}


MccRobot::~MccRobot(void)
{
	// Release declarations.
	for (size_t i = 0, len = this->m_decls.size(); i < len; ++i) {
		delete this->m_decls[i];
	}
}


void MccRobot::initialize(MccDeclarationList *decl_list)
{
	// cout << "Hello" << endl;
	if (decl_list != nullptr) {
		// copy to m_decls
		// cout << "Not empty program" << endl;
		decl_list->copy_to_list(this->m_decls);
	}


}


void MccRobot::generate_code()
{
	// Initialization.
	this->m_current_break_label = "";
	this->m_current_continue_label = "";
	this->m_false_branch_nums = 0;
	this->m_current_func_decl = nullptr; // Indicates global scope.

	cout << "MccRobot generation." << endl;

	for (size_t i = 0, len = this->m_decls.size(); i < len; ++i) {
		this->m_decls[i]->generate_code();
	}
}


void MccRobot::set_current_break_label(const string &new_label)
{
	this->m_current_break_label = new_label;
}


string MccRobot::get_current_break_label() const
{
	return this->m_current_break_label;
}


void MccRobot::set_current_continue_label(const string &new_label)
{
	this->m_current_continue_label = new_label;
}


string MccRobot::get_current_continue_label() const
{
	return this->m_current_continue_label;
}


void MccRobot::set_current_func_decl(MccFunctionDeclaration *new_fun)
{
	this->m_current_func_decl = new_fun;
}


MccFunctionDeclaration* MccRobot::get_current_func_decl() const
{
	return this->m_current_func_decl;
}


IdentifierInfo* MccRobot::add_global_decl(const string &name, int decl_size)
{
	IdentifierMap::iterator iter = this->m_decl_infos.find(name);
	IdentifierInfo *info = nullptr;
	if (iter == this->m_decl_infos.end()) {
		IdentifierInfo *info = new IdentifierInfo;
		if (decl_size == 0) {
			info->id_type = FUNC;
		} else if (decl_size == 4) {
			info->id_type = NOMARL_VAR;
		} else {
			info->id_type = ARRAY_VAR;
		}

		//@todo position field.

		this->m_decl_infos.insert(IdentifierMap::value_type(name, info));
	} else {
		info = iter->second;
	}

	return info;	
}


string MccRobot::generate_false_branch_label()
{
	static string base_name = "false_branch_";
	return Utility::string_concat_int(base_name, this->m_false_branch_nums++);
}



