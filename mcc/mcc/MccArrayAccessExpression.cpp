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
	// cout << "MccArrayAccessExpression generation." << endl;
	this->m_index->generate_code();
	code_buffer += "sw $a0 0($sp)\n";
	code_buffer += "addiu $sp $sp -4\n";
	this->m_id->generate_code();
	code_buffer += "lw $a0 4($sp)\n";
	code_buffer += "addiu $sp $sp 4\n";
	code_buffer += "multiu $s0 $s0 4\n";
	code_buffer += "addiu $a0 $a0 $s0\n";

	return 0;
}
