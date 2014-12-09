#pragma once
#include "mccsemanticerrorchecker.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class MccVariableDeclaration;
class MccFunctionDeclaration;

/**
 * @brief Check whether there is a conflict among identifiers.
 */
class MccIdentifierConflictChecker :
	public MccSemanticErrorChecker
{
public:
	struct IdentifierInfo {
		string id_name;
		int line_no;
		void *scope; // nullptr for global, other is function global.
		bool is_fun; // true, function; false, variable.
		bool contain_fun_def; // true, already has definition.
	};

	MccIdentifierConflictChecker(void);
	virtual ~MccIdentifierConflictChecker(void);

	void detect(MccVariableDeclaration *var);
	void detect(MccFunctionDeclaration *fun);


private:
	vector<IdentifierInfo*> m_ids;
	void *m_current_scope;
};

