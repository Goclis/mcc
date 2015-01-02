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
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccArrayAccessExpression generation.\n";
#endif

	// Gen(m_id).
	this->m_id->generate_code();

	// Push $v0.
	code_buffer += 
		"sw $v0, 0H($sp)\n"
		"addiu $v1, $zero, 1\n"
		"subu $sp, $sp, $v1\n";
	robot
		.add_code("sw $v0, 0H($sp)")
		.add_code("addiu $v1, $zero, 1")
		.add_code("subu $sp, $sp, $v1");
	
	// Gen(m_index).
	this->m_index->generate_code();

	// Pop $v1.
	code_buffer += 
		"lw $v1, 1H($sp)\n"
		"addiu $sp, $sp, 1\n";
	robot
		.add_code("lw $v1, 1H($sp)")
		.add_code("addiu $sp, $sp, 1");

	// $v0 = Memory[$v0 + $v1].
	code_buffer += 
		"add $v0, $v0, $v1\n"
		"lw $v0, 0H($v0)\n";
	robot
		.add_code("add $v0, $v0, $v1")
		.add_code("lw $v0, 0H($v0)");

	return 0;
}
