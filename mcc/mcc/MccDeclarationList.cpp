#include "MccDeclarationList.h"
#include "MccDeclaration.h"


MccDeclarationList::MccDeclarationList(MccDeclaration *first)
{
	this->push_back(first);
}


MccDeclarationList::~MccDeclarationList(void)
{
	// No need to release declarations, because they will be passed to other,
	// just clear list.
	this->m_decl_list.clear();
}


void MccDeclarationList::push_back(MccDeclaration *decl)
{
	if (decl != nullptr) {
		this->m_decl_list.push_back(decl);
	}
}


void MccDeclarationList::copy_to_list(vector<MccDeclaration *> &list)
{
	for (size_t i = 0, len = this->m_decl_list.size(); i < len; ++i) {
		list.push_back(this->m_decl_list[i]);
	}
}


void MccDeclarationList::copy_to_list_derived(vector<MccVariableDeclaration *> &list)
{
	for (size_t i = 0, len = this->m_decl_list.size(); i < len; ++i) {
		list.push_back((MccVariableDeclaration *) (this->m_decl_list[i]));
	}
}
