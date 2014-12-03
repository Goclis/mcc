#include "MccArrayAccessExpression.h"
#include "MccIdentifier.h"


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
	cout << "MccArrayAccessExpression generation." << endl;
	this->m_index->generate_code();
	cout << "sw $a0 0($sp)" << endl;
	cout << "addiu $sp $sp -4" << endl;
	this->m_id->generate_code();
	cout << "lw $a0 4($sp)" << endl;
	cout << "addiu $sp $sp 4" << endl;
	cout << "multiu $s0 $s0 4" << endl;
	cout << "addiu $a0 $a0 $s0" << endl;

	return 0;
}
