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
	int ar_size = func_decl->m_ar_size;
	int args_size = func_decl->m_parameter_list.size();
	
	// The return statement is out of any if statements, so the function 
	// declaration no need to generate codes for retrieving activation record.
	if (func_decl->get_if_levels() == 0) {
		func_decl->set_has_retrieved();
	}

	return 0;
}
