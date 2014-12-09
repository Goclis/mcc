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
	code_buffer += "MccReturnStatement generation.\n";
	MccFunctionDeclaration *func_decl = robot.get_current_func_decl();

	// Gen(m_expr).
	this->m_expr->generate_code();

	// Retrieving activation record.
	int ar_size = func_decl->get_ar_size();
	int vars_size = func_decl->get_vars_size();
	int final_pop_size = ar_size - vars_size;

	if (vars_size > 0) {
		code_buffer += Utility::string_concat_int("addiu $sp $sp ", vars_size)
			+ "\n";
	}
	code_buffer += "lw $ra 4($sp)\n";
	code_buffer += Utility::string_concat_int("addiu $sp $sp ", final_pop_size)
		+ "\n";
	code_buffer += "lw $fp 0($sp)\n";
	code_buffer += "jr $ra\n";
	
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
