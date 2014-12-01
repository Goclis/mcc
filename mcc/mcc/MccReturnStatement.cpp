#include "MccReturnStatement.h"
#include "MccRobot.h"
#include "MccFunctionDeclaration.h"
#include "MccExpression.h"

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
	cout << "MccReturnStatement generation." << endl;

	MccFunctionDeclaration *func_decl = theMccRobot().get_current_func_decl();

	// Generate code for expression.
	this->m_expr->generate_code();

	// Retrieving activation record.
	int ar_size = func_decl->get_ar_size();
	int vars_size = func_decl->get_vars_size();
	int final_pop_size = ar_size - vars_size;

	cout << "addiu $sp $sp " << vars_size << endl;
	cout << "lw $ra 4($sp)" << endl;
	cout << "addiu $sp $sp " << final_pop_size << endl;
	cout << "lw $fp 0($sp)" << endl;
	cout << "jr $ra" << endl;
	
	// The return statement is out of any if statements, so the function 
	// declaration no need to generate codes for retrieving activation record.
	if (func_decl->get_cond_stmt_level() == 0) {
		func_decl->set_has_retrieved();
	}

	return 0;
}
