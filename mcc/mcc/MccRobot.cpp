#include "MccRobot.h"
#include "MccDeclarationList.h"
#include "MccDeclaration.h"
#include "Utility.h"
#include "MccSemanticError.h"
#include "MccVariableTypeChecker.h"
#include "MccMethodParameterNameExistChecker.h"
#include "MccJumpInWhileChecker.h"
#include "MccIdentifierConflictChecker.h"
#include "MccVariableReferenceChecker.h"
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

	// Release information of variable.
	for (IdentifierMap::iterator iter = m_decl_infos.begin(),
			the_end = m_decl_infos.end(); iter != the_end; ++iter) {
		if (iter->second != nullptr) {
			delete iter->second;
		}
	}
	m_decl_infos.clear();
}


void MccRobot::initialize(MccDeclarationList *decl_list)
{
	if (decl_list != nullptr) {
		// copy to m_decls
		decl_list->copy_to_list(this->m_decls);
	}
}


void MccRobot::generate_code()
{
	// Initialization.
	this->m_current_break_label = "";
	this->m_current_continue_label = "";
	this->m_global_var_code_buffer = "";
	this->m_code_buffer = "";
	this->m_branch_nums = 0;
	this->m_while_nums = 0;
	this->m_quick_branch_nums = 0;
	this->m_global_var_size = 0;
	this->m_current_func_decl = nullptr; // Indicates global scope.

	cout << "MccRobot generation." << endl;

	for (size_t i = 0, len = this->m_decls.size(); i < len; ++i) {
		this->m_decls[i]->generate_code();
	}

	cout << this->m_global_var_code_buffer;
	cout << this->m_code_buffer;
}


bool MccRobot::check_semantic_error()
{
	vector<MccSemanticErrorChecker*> checkers;
	checkers.push_back(new MccVariableTypeChecker);
	checkers.push_back(new MccMethodParameterNameExistChecker);
	checkers.push_back(new MccJumpInWhileChecker);
	checkers.push_back(new MccIdentifierConflictChecker);
	checkers.push_back(new MccVariableReferenceChecker);
	
	bool no_error = true;
	for (size_t i = 0; i < checkers.size(); ++i) {
		m_current_checker = checkers[i];

		for (size_t j = 0; j < m_decls.size(); ++j) {
			m_decls[j]->semantic_detect();
		}

		vector<MccSemanticError*> error_list = m_current_checker->get_error_list();
		if (no_error && error_list.size() != 0) {
			no_error = false;
		}
		
		for (size_t ei = 0; ei < error_list.size(); ++ei) {
			error_list[ei]->report();
		}
	}

	for (size_t i = 0; i < checkers.size(); ++i) {
		delete checkers[i];
	}
	return no_error;
}


IdentifierInfo* MccRobot::add_global_decl(const string &name, int decl_size)
{
	IdentifierMap::iterator iter = this->m_decl_infos.find(name);
	IdentifierInfo *info = nullptr;
	if (iter == this->m_decl_infos.end()) {
		IdentifierInfo *info = new IdentifierInfo;
		info->scope = nullptr;
		if (decl_size == 0) {
			info->id_type = FUNC;
		} else if (decl_size == 4) {
			info->id_type = NOMARL_VAR;
			this->m_global_var_size += 4;
			info->position = Utility::string_concat_int("", this->m_global_var_size);
		} else {
			info->id_type = ARRAY_VAR;
			this->m_global_var_size += decl_size;
			info->position = Utility::string_concat_int("", this->m_global_var_size);
		}

		this->m_decl_infos.insert(IdentifierMap::value_type(name, info));
	} else {
		info = iter->second;
	}

	return info;	
}


string MccRobot::generate_branch_label()
{
	static string base_name = "branch_";
	return Utility::string_concat_int(base_name, m_branch_nums++);
}


IdentifierInfo* MccRobot::get_identifier_info(const string &name)
{
	IdentifierMap::iterator iter = this->m_decl_infos.find(name);
	if (iter != this->m_decl_infos.end()) {
		return iter->second;
	} else {
		return nullptr;
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


string& MccRobot::get_code_buffer()
{
	return this->m_code_buffer;
}


string& MccRobot::get_global_var_code_buffer()
{
	return this->m_global_var_code_buffer;
}


MccSemanticErrorChecker* MccRobot::get_current_checker() const
{
	return m_current_checker;
}

