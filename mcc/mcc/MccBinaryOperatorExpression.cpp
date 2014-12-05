#include "MccBinaryOperatorExpression.h"
#include "MccRobot.h"


MccBinaryOperatorExpression::MccBinaryOperatorExpression(
		BINARY_OPERATOR op, 
		MccExpression *left, 
		MccExpression *right)
	: m_operator(op),
	  m_left_operand(left),
	  m_right_operand(right)
{
}


MccBinaryOperatorExpression::~MccBinaryOperatorExpression(void)
{
	if (this->m_left_operand != nullptr) {
		delete this->m_left_operand;
	}

	if (this->m_right_operand != nullptr) {
		delete this->m_right_operand;
	}
}


int MccBinaryOperatorExpression::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	code_buffer += "MccBinaryOperatorExpression generation.\n";
	string quick_branch_label;

	// Gen(m_left_operand).
	this->m_left_operand->generate_code();

	// Need to add more operation for binary logical operator, && and ||.
	if (this->m_operator == AND_BINARY) {
		// If $v0 is 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_branch_label();
		code_buffer += "beq $v0 $zero " + quick_branch_label + "\n";
	} else if (this->m_operator == OR_BINARY) {
		// If $v0 is not 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_branch_label();
		code_buffer += "bne $v0 $zero " + quick_branch_label + "\n";
	}

	// Push $v0.
	code_buffer += "sw $v0 0($sp)\n";
	code_buffer += "subiu $sp $sp 4\n";

	// Gen(m_right_operand).
	this->m_right_operand->generate_code();

	// Pop $v1.
	code_buffer += "lw $v1 4($sp)\n";
	code_buffer += "addiu $sp $sp 4\n";

	// According to operator, use different instructions.
	switch (this->m_operator)
	{
	case OR_BINARY:
		{
			code_buffer += "sltu $v0 $zero $v0\n";
			break;
		}

	case EQ_BINARY:
		{
			string branch_label = robot.generate_branch_label();
			string branch_end = branch_label + "_end";
			code_buffer += "beq $v0 $v1 " + branch_label + "\n";
			code_buffer += "addiu $v0 $zero 0\n";
			code_buffer += "j " + branch_end + "\n";
			code_buffer += branch_label + ":\n";
			code_buffer += "addiu $v0 $zero 1\n";
			code_buffer += branch_end + ":\n";
			break;
		}

	case NE_BINARY:
		{
			string branch_label = robot.generate_branch_label();
			string branch_end = branch_label + "_end";
			code_buffer += "bne $v0 $v1 " + branch_label + "\n";
			code_buffer += "addiu $v0 $zero 0\n";
			code_buffer += "j " + branch_end + "\n";
			code_buffer += branch_label + ":\n";
			code_buffer += "addiu $v0 $zero 1\n";
			code_buffer += branch_end + ":\n";
			break;
		}

	case LE_BINARY:
		{
			code_buffer += "slt $v0 $v0 $v1\n";
			code_buffer += "sltu $v0 $zero $v0\n";
			break;
		}

	case LT_BINARY:
		{
			code_buffer += "slt $v0 $v1 $v0\n";
			break;
		}

	case GT_BINARY:
		{
			code_buffer += "slt $v0 $v0 $v1\n";
			break;
		}

	case GE_BINARY:
		{
			code_buffer += "slt $v0 $v1 $v0\n";
			code_buffer += "sltu $v0 $zero $v0\n";
			break;
		}

	case AND_BINARY:
		{
			code_buffer += "and $v0 $v1 $v0\n";
			code_buffer += "sltu $v0 $zero $v0\n";
			break;
		}

	case PLUS_BINARY:
		{
			code_buffer += "add $v0 $v1 $v0\n";
			break;
		}

	case MINUS_BINARY:
		{
			code_buffer += "sub $v0 $v1 $v0\n";
			break;
		}

	case MULT_BINARY:
		{
			code_buffer += "mult $v1 $v0\n";
			code_buffer += "mflo $v0\n";
			break;
		}

	case DIV_BINARY:
		{
			code_buffer += "div $v1 $v0\n";
			code_buffer += "mflo $v0\n";
			break;
		}

	case MD_BINARY:
		{
			code_buffer += "div $v1 $v0\n";
			code_buffer += "mfhi $v0\n";
			break;
		}

	case BIT_AND_BINARY:
		{
			code_buffer += "and $v0 $v1 $v0\n";
			break;
		}

	case EXCLUSIVE_BINARY:
		{
			code_buffer += "xor $v0 $v1 $v0\n";
			break;
		}

	case LSHIFT_BINARY:
		{
			code_buffer += "sllv $v0 $v1 $v0\n";
			break;
		}

	case RSHIFT_BINARY:
		{
			code_buffer += "srlv $v0 $v1 $v0\n";
			break;
		}

	case BIT_OR_BINARY:
		{
			code_buffer += "or $v0 $v1 $v0\n";
			break;
		}
	}

	if (this->m_operator == AND_BINARY || this->m_operator == OR_BINARY) {
		code_buffer += quick_branch_label + ":\n";
	}

	return 0;
}
