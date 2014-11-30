#include "MccRobot.h"
#include "MccDeclarationList.h"
#include "MccDeclaration.h"
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
	cout << "Hello" << endl;
	if (decl_list != nullptr) {
		// copy to m_decls
		cout << "Not empty program" << endl;
		decl_list->copy_to_list(this->m_decls);
	}


}


void MccRobot::generate_code() const
{
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



