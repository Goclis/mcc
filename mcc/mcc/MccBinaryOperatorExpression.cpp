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
	// cout << "MccBinaryOperatorExpression generation." << endl;
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
	this->m_left_operand->generate_code();
	string quick_branch_label;
	// Need to add more operation for binary logical operator, && and ||.
	if (this->m_operator == AND_BINARY) {
		// If $a0 is 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_quick_branch_label();
		code_buffer += "beq $a0 0 " + quick_branch_label + "\n";
	} else if (this->m_operator == OR_BINARY) {
		// If $a0 is not 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_quick_branch_label();
		code_buffer += "beq $a0 1 " + quick_branch_label + "\n";
	}
	code_buffer += "sw $a0 0($sp)\n";
	code_buffer += "addiu $sp $sp -4\n";
	this->m_right_operand->generate_code();
	code_buffer += "lw $s0 4($sp)\n";
	code_buffer += "addiu $sp $sp 4\n";
	switch (this->m_operator)
	{
	case OR_BINARY:
		{
			code_buffer += "mov $a0 $s0 || $a0\n";
			break;
		}

	case EQ_BINARY:
		{
			code_buffer += "mov $a0 $s0 == $a0\n";
			break;
		}

	case NE_BINARY:
		{
			code_buffer += "mov $a0 $s0 != $a0\n";
			break;
		}

	case LE_BINARY:
		{
			code_buffer += "mov $a0 $s0 <= $a0\n";
			break;
		}

	case LT_BINARY:
		{
			code_buffer += "mov $a0 $s0 < $a0\n";
			break;
		}

	case GT_BINARY:
		{
			code_buffer += "mov $a0 $s0 > $a0\n";
			break;
		}

	case GE_BINARY:
		{
			code_buffer += "mov $a0 $s0 >= $a0\n";
			break;
		}

	case AND_BINARY:
		{
			code_buffer += "mov $a0 $s0 && $a0\n";
			break;
		}

	case PLUS_BINARY:
		{
			code_buffer += "mov $a0 $s0 + $a0\n";
			break;
		}

	case MINUS_BINARY:
		{
			code_buffer += "mov $a0 $s0 - $a0\n";
			break;
		}

	case MULT_BINARY:
		{
			code_buffer += "mov $a0 $s0 * $a0\n";
			break;
		}

	case DIV_BINARY:
		{
			code_buffer += "mov $a0 $s0 / $a0\n";
			break;
		}

	case MD_BINARY:
		{
			code_buffer += "mov $a0 $s0 % $a0\n";
			break;
		}

	case BIT_AND_BINARY:
		{
			code_buffer += "mov $a0 $s0 & $a0\n";
			break;
		}

	case EXCLUSIVE_BINARY:
		{
			code_buffer += "mov $a0 $s0 ^ $a0\n";
			break;
		}

	case LSHIFT_BINARY:
		{
			code_buffer += "mov $a0 $s0 << $a0\n";
			break;
		}

	case RSHIFT_BINARY:
		{
			code_buffer += "mov $a0 $s0 >> $a0\n";
			break;
		}

	case BIT_OR_BINARY:
		{
			code_buffer += "mov $a0 $s0 | $a0\n";
			break;
		}
	}

	if (this->m_operator == AND_BINARY || this->m_operator == OR_BINARY) {
		code_buffer += quick_branch_label + ":\n";
	}

	return 0;
}
