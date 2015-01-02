#include "MccBinaryOperatorExpression.h"
#include "MccRobot.h"
#include "MccSemanticErrorChecker.h"


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
#ifdef DEBUG_MODE
	code_buffer += "MccBinaryOperatorExpression generation.\n";
#endif
	string quick_branch_label;

	// Gen(m_left_operand).
	this->m_left_operand->generate_code();

	// Need to add more operation for binary logical operator, && and ||.
	if (this->m_operator == AND_BINARY) {
		// If $v0 is 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_branch_label();
		code_buffer +=
			"beq $v0, $zero, " + quick_branch_label + "\n"
			"srlv $v1, $zero, $zero\n";
		robot
			.add_code("beq $v0, $zero, " + quick_branch_label)
			.add_code("srlv $v1, $zero, $zero");
	} else if (this->m_operator == OR_BINARY) {
		// If $v0 is not 0, no need to calculate the right operand.
		quick_branch_label = robot.generate_branch_label();
		code_buffer +=
			"bne $v0, $zero, " + quick_branch_label + "\n"
			"srlv $v1, $zero, $zero\n";
		robot
			.add_code("bne $v0, $zero, " + quick_branch_label)
			.add_code("srlv $v1, $zero, $zero");
	}

	// Push $v0.
	code_buffer += 
		"sw $v0, 0H($sp)\n"
		"addiu $v0, $zero, 1\n"
		"subu $sp, $sp, $v0\n";
	robot
		.add_code("sw $v0, 0H($sp)")
		.add_code("addiu $v0, $zero, 1")
		.add_code("subu $sp, $sp, $v0");

	// Gen(m_right_operand).
	this->m_right_operand->generate_code();

	// Pop $v1.
	code_buffer += 
		"lw $v1, 1H($sp)\n"
		"addiu $sp, $sp, 1\n";
	robot
		.add_code("lw $v1, 1H($sp)")
		.add_code("addiu $sp, $sp, 1");

	// According to operator, use different instructions.
	switch (this->m_operator)
	{
	case OR_BINARY:
		{
			code_buffer += 
				"sltu $v0, $zero, $v0\n";
			robot
				.add_code("sltu $v0, $zero, $v0");
			break;
		}

	case EQ_BINARY:
		{
			string branch_label = robot.generate_branch_label();
			string branch_end = branch_label + "_end";
			code_buffer += 
				"beq $v0, $v1, " + branch_label + "\n"
				"srlv $v1, $zero, $zero\n"
				"addiu $v0, $zero, 0\n"
				"j " + branch_end + "\n"
				"srlv $v1, $zero, $zero" +
				branch_label + ":\n"
				"addiu $v0, $zero, 1\n" +
				branch_end + ":\n";

			robot
				.add_code("beq $v0, $v1, " + branch_label)
				.add_code("srlv $v1, $zero, $zero")
				.add_code("addiu $v0, $zero, 0")
				.add_code("j " + branch_end)
				.add_code("srlv $v1, $zero, $zero")
				.add_code(branch_label + ":")
				.add_code("addiu $v0, $zero, 1")
				.add_code(branch_end + ":");
			break;
		}

	case NE_BINARY:
		{
			string branch_label = robot.generate_branch_label();
			string branch_end = branch_label + "_end";
			code_buffer += 
				"bne $v0 $v1 " + branch_label + "\n"
				"srlv $v1, $zero, $zero\n"
				"addiu $v0, $zero, 0\n"
				"j " + branch_end + "\n"
				"srlv $v1, $zero, $zero\n" +
				branch_label + ":\n"
				"addiu $v0, $zero, 1\n" +
				branch_end + ":\n";

			robot
				.add_code("bne $v0, $v1, " + branch_label)
				.add_code("srlv $v1, $zero, $zero")
				.add_code("addiu $v0, $zero, 0")
				.add_code("j " + branch_end)
				.add_code("srlv $v1, $zero, $zero")
				.add_code(branch_label + ":")
				.add_code("addiu $v0, $zero, 1")
				.add_code(branch_end + ":");
			break;
		}

	case LE_BINARY:
		{
			code_buffer += 
				"slt $v0, $v0, $v1\n"
				"sltu $v0, $zero, $v0\n";

			robot
				.add_code("slt $v0, $v0, $v1")
				.add_code("sltu $v0, $zero, $v0");
			break;
		}

	case LT_BINARY:
		{
			code_buffer += 
				"slt $v0, $v1, $v0\n";

			robot
				.add_code("slt $v0, $v1, $v0");
			break;
		}

	case GT_BINARY:
		{
			code_buffer += 
				"slt $v0, $v0, $v1\n";

			robot
				.add_code("slt $v0, $v0, $v1");
			break;
		}

	case GE_BINARY:
		{
			code_buffer += 
				"slt $v0, $v1, $v0\n"
				"sltu $v0, $zero, $v0\n";

			robot
				.add_code("slt $v0, $v1, $v0")
				.add_code("sltu $v0, $zero, $v0");
			break;
		}

	case AND_BINARY:
		{
			code_buffer += 
				"and $v0, $v1, $v0\n"
				"sltu $v0, $zero, $v0\n";

			robot
				.add_code("and $v0, $v1, $v0")
				.add_code("sltu $v0, $zero, $v0");
			break;
		}

	case PLUS_BINARY:
		{
			code_buffer += 
				"add $v0, $v1, $v0\n";

			robot
				.add_code("add $v0, $v1, $v0");
			break;
		}

	case MINUS_BINARY:
		{
			code_buffer += 
				"sub $v0, $v1, $v0\n";

			robot
				.add_code("sub $v0, $v1, $v0");
			break;
		}

	case MULT_BINARY:
		{
			code_buffer += 
				"mult $v1, $v0\n"
				"mflo $v0\n";

			robot
				.add_code("mult $v1, $v0")
				.add_code("mflo $v0");
			break;
		}

	case DIV_BINARY:
		{
			code_buffer += 
				"div $v1, $v0\n"
				"mflo $v0\n";

			robot
				.add_code("div $v1, $v0")
				.add_code("mflo $v0");
			break;
		}

	case MD_BINARY:
		{
			code_buffer += 
				"div $v1, $v0\n"
				"mfhi $v0\n";

			robot
				.add_code("div $v1, $v0")
				.add_code("mfhi $v0");
			break;
		}

	case BIT_AND_BINARY:
		{
			code_buffer += 
				"and $v0, $v1, $v0\n";

			robot
				.add_code("and $v0, $v1, $v0");
			break;
		}

	case EXCLUSIVE_BINARY:
		{
			code_buffer += 
				"xor $v0, $v1, $v0\n";

			robot
				.add_code("xor $v0, $v1, $v0");
			break;
		}

	case LSHIFT_BINARY:
		{
			code_buffer += 
				"sllv $v0, $v1, $v0\n";

			robot
				.add_code("sllv $v0, $v1, $v0");
			break;
		}

	case RSHIFT_BINARY:
		{
			code_buffer += 
				"srlv $v0, $v1, $v0\n";

			robot
				.add_code("srlv $v0, $v1, $v0");
			break;
		}

	case BIT_OR_BINARY:
		{
			code_buffer += 
				"or $v0, $v1, $v0\n";

			robot
				.add_code("or $v0, $v1, $v0");
			break;
		}
	}

	if (this->m_operator == AND_BINARY || this->m_operator == OR_BINARY) {
		code_buffer += 
			quick_branch_label + ":\n";
		robot
			.add_code(quick_branch_label + ":");
	}

	return 0;
}


void MccBinaryOperatorExpression::semantic_detect()
{
	theMccRobot().get_current_checker()->detect(this);
}
