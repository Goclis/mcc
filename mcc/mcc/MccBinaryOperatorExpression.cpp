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
	cout << "MccBinaryOperatorExpression generation." << endl;
	MccRobot &robot = theMccRobot();
	this->m_left_operand->generate_code();
	string quick_branch_label;
	// Need to add more operation for binary logical operator, && and ||.
	if (this->m_operator == AND_BINARY) {
		// If $a0 is 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_quick_branch_label();
		cout << "beq $a0 0 " << quick_branch_label << endl;
	} else if (this->m_operator == OR_BINARY) {
		// If $a0 is not 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_quick_branch_label();
		cout << "beq $a0 1 " << quick_branch_label << endl;
	}
	cout << "sw $a0 0($sp)" << endl;
	cout << "addiu $sp $sp -4" << endl;
	this->m_right_operand->generate_code();
	cout << "lw $s0 4($sp)" << endl;
	cout << "addiu $sp $sp 4" << endl;
	switch (this->m_operator)
	{
	case OR_BINARY:
		{
			break;
		}

	case EQ_BINARY:
		{
			break;
		}

	case NE_BINARY:
		{
			break;
		}

	case LE_BINARY:
		{
			break;
		}

	case LT_BINARY:
		{
			break;
		}

	case GT_BINARY:
		{
			break;
		}

	case GE_BINARY:
		{
			break;
		}

	case AND_BINARY:
		{
			break;
		}

	case PLUS_BINARY:
		{
			break;
		}

	case MINUS_BINARY:
		{
			break;
		}

	case MULT_BINARY:
		{
			break;
		}

	case DIV_BINARY:
		{
			break;
		}

	case MD_BINARY:
		{
			break;
		}

	case BIT_AND_BINARY:
		{
			break;
		}

	case EXCLUSIVE_BINARY:
		{
			break;
		}

	case LSHIFT_BINARY:
		{
			break;
		}

	case RSHIFT_BINARY:
		{
			break;
		}

	case BIT_OR_BINARY:
		{
			break;
		}
	}

	if (this->m_operator == AND_BINARY || this->m_operator == OR_BINARY) {
		cout << quick_branch_label << ":" << endl;
	}

	return 0;
}
