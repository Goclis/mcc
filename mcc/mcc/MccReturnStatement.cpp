#include "MccReturnStatement.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"
#include "MccFunctionDeclaration.h"
#include "MccExpression.h"
#include "Utility.h"

MccReturnStatement::MccReturnStatement(MccExpression *expr)
	: m_expr(expr)
{

}

MccReturnStatement::~MccReturnStatement()
{
	if (this->m_expr != nullptr) {
		delete this->m_expr;
	}	
}


int MccReturnStatement::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccReturnStatement generation.\n";
#endif
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();

	// Gen(m_expr).
	this->m_expr->generate_code();

	// Retrieving activation record.
	int parameter_size = func_decl->m_parameter_size;
	int local_var_size = func_decl->m_local_var_size;
	
	// Retrieve local variables.
	if (local_var_size > 0) {
		code_buffer += 
			Utility::string_concat_int("addiu $sp $sp ", local_var_size) + "\n";
		robot
			.add_code(Utility::string_concat_int("addiu $sp, $sp, ", local_var_size));
	}

	// Restore $ra.
	code_buffer += 
		"lw $ra 1($sp)\n";
	robot
		.add_code("lw $ra, 1H($sp)");

	// Pop parameters, $ra and $fp.
	code_buffer += 
		Utility::string_concat_int("addiu $sp $sp ", parameter_size + 2) + "\n"
		"lw $fp 0($sp)\n"
		"jr $ra\n";
	robot
		.add_code(Utility::string_concat_int("addiu $sp, $sp, ", parameter_size + 2))
		.add_code("lw $t0, 0H($sp)")
		.add_code("jr $ra")
		.add_code("srlv $v1, $zero, $zero");
	
	// The return statement is out of any if statements, so the function 
	// declaration no need to generate codes for retrieving activation record.
	if (func_decl->get_cond_stmt_level() == 0) {
		func_decl->set_has_retrieved();
	}

	return 0;
}


void MccReturnStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
