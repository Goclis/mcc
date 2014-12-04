#include "MccVariableDeclaration.h"
#include "MccIdentifier.h"
#include "MccFunctionDeclaration.h"
#include "MccRobot.h"
#include "Utility.h"


MccVariableDeclaration::MccVariableDeclaration(
		TYPE_SPEC type_spec, 
		MccIdentifier *identifier, 
		int array_size)
	: MccDeclaration(type_spec, identifier),
	  m_array_size(array_size)
{
}


MccVariableDeclaration::~MccVariableDeclaration(void)
{
	// Identifier released by base class destructor.
}


int MccVariableDeclaration::generate_code()
{
	// cout << "MccVariableDeclaration generation." << endl;
	MccRobot &robot = theMccRobot();
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();
	int stack_used = 4;
	bool is_array_variable = (this->m_array_size != -1);
	if (is_array_variable) {
		stack_used = 4 * this->m_array_size;
	}
	
	string var_name = this->get_decl_name();
	
	if (func_decl != nullptr) {
		func_decl->add_local_var_decl(var_name, stack_used);
		robot.get_code_buffer() 
			+= Utility::string_concat_int("subiu $sp $sp ", stack_used) + "\n";
	} else {
		// Global variable declaration.
		robot.add_global_decl(var_name, stack_used);
		robot.get_global_var_code_buffer() 
			+= Utility::string_concat_int("subiu $sp $sp ", stack_used) + "\n";
	}

	return stack_used;
}
