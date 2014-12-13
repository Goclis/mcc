#include "MccArrayAccessExpression.h"
#include "MccIdentifier.h"
#include "MccRobot.h"


MccArrayAccessExpression::MccArrayAccessExpression(void)
	: m_id(nullptr),
	  m_index(nullptr)
{
}


MccArrayAccessExpression::MccArrayAccessExpression(MccIdentifier *id, MccExpression *index)
	: m_id(id),
	  m_index(index)
{

}


MccArrayAccessExpression::~MccArrayAccessExpression(void)
{
	if (this->m_id != nullptr) {
		delete this->m_id;
	}

	if (this->m_index != nullptr) {
		delete this->m_index;
	}
}


int MccArrayAccessExpression::generate_code() const
{
	string &code_buffer = theMccRobot().get_code_buffer();
	code_buffer += "MccArrayAccessExpression generation.\n";

	// Gen(m_id).
	this->m_id->generate_code();

	// Push $v0.
	code_buffer += 
		"sw $v0 0($sp)\n"
		"addiu $v1 $zero 4\n"
		"subu $sp $sp $v1\n";
	
	// Gen(m_index).
	this->m_index->generate_code();
	
	// $v0 *= 4.
	code_buffer += 
		"addiu $v1 $zero 4\n"
		"mult $v0 $v1\n"
		"mflo $v0\n";

	// Pop $v1.
	code_buffer += 
		"lw $v1 4($sp)\n"
		"addiu $sp $sp 4\n";

	// $v0 = Memory[$v0 + $v1].
	code_buffer += 
		"add $v0 $v0 $v1\n"
		"lw $v0 0($v0)\n";
		

	return 0;
}
