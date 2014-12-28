#include "MccFunctionDeclaration.h"
#include "MccAssignStatement.h"
#include "MccExpression.h"
#include "MccIdentifier.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"
#include "Utility.h"


MccAssignStatement::MccAssignStatement( 
	MccExpression *right, 
	MccIdentifier *identifier, 
	MccExpression *array_index_expr /*= nullptr*/, 
	MccExpression *port_expr /*= nullptr*/ )
	: m_right_operand(right),
	  m_identifier(identifier),
	  m_array_index_expr(array_index_expr),
	  m_port_expr(port_expr)
{

}


MccAssignStatement::~MccAssignStatement(void)
{
	if (nullptr != m_identifier) {
		delete m_identifier;
	}
	if (nullptr != m_port_expr) {
		delete m_port_expr;
	}
	if (nullptr != m_array_index_expr) {
		delete m_array_index_expr;
	}
	if (this->m_right_operand != nullptr) {
		delete this->m_right_operand;
	}
}


int MccAssignStatement::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccAssignStatement generation.\n";
#endif
	
	// Gen(m_right_operand).
	m_right_operand->generate_code();

	// Push($v0), save the result of right operand.
	code_buffer +=
		"sw $v0 0($sp)\n"
		"addiu $v1 $zero 1\n"
		"subu $sp $sp $v1\n";

	// Gen(`m_left`).
	if (nullptr == m_port_expr) {
		// Left operand is not port expression.
		MccFunctionDeclaration *func_decl = robot.get_current_func_decl();
		IdentifierInfo *info = nullptr;
		if (nullptr == func_decl) {
			info = robot.get_identifier_info(m_identifier->m_name);
		} else {
			info = func_decl->search_identifier_info(m_identifier->m_name);
		}

		if (nullptr == info) {
			exit(1);
		}

		if (nullptr == info->scope) {
			// Global variable.
			string global_fp = robot.get_global_fp();
			code_buffer +=
				"addiu $v0 $zero " + global_fp + "\n" +
				Utility::string_concat_int("addiu $v1 $zero ", info->position) + "\n"
				"subu $v0 $v0 $v1\n";
		} else {
			// Local variable.
			if (PARAMETER_VAR == info->id_type) {
				code_buffer +=
					Utility::string_concat_int("addiu $v0 $fp ", info->position) + "\n";
			} else {
				code_buffer +=
					Utility::string_concat_int("addiu $v1 $zero", info->position) + "\n"
					"subu $v0 $fp $v1\n";
			}
		}

		if (nullptr != m_array_index_expr) {
			// Array vairbale needs more instructions.
			// Push $v0.
			code_buffer +=
				"sw $v0 0($sp)\n"
				"addiu $v1 $zero 1\n"
				"subu $sp $sp $v1\n";

			// Array index.
			m_array_index_expr->generate_code();

			// Pop $v1
			code_buffer +=
				"lw $v1 1($sp)\n"
				"addiu $sp $sp 1\n";

			// Add together.
			code_buffer +=
				"add $v0 $v0 $v1\n";
		}
	} else {
		// Left operand is port expression.
		m_port_expr->generate_code();
	}

	// Pop $v1.
	code_buffer += 
		"lw $v1 1($sp)\n"
		"addiu $sp $sp 1\n";

	// Memory[$v0] = $v1 and save the result to $v0.
	code_buffer += 
		"sw $v1 0($v0)\n"
		"addu $v0 $zero $v1\n";

	return 0;
}


void MccAssignStatement::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
