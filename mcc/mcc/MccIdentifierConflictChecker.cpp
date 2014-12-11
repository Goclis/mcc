#include "MccIdentifierConflictChecker.h"
#include "MccIdentifierConflictError.h"
#include "MccVariableDeclaration.h"
#include "MccFunctionDeclaration.h"
#include "MccFuncParameter.h"
#include "MccIdentifier.h"


MccIdentifierConflictChecker::MccIdentifierConflictChecker(void)
{
	m_current_scope = nullptr;
}


MccIdentifierConflictChecker::~MccIdentifierConflictChecker(void)
{
}


void MccIdentifierConflictChecker::detect(MccVariableDeclaration *var)
{
	string var_name = var->get_decl_name();
	IdentifierInfo *info = nullptr;
	for (size_t i = 0, len = m_ids.size(); i < len; ++i) {
		info = m_ids[i];
		if (info->id_name == var_name) {
			// The existent identifier is function.
			if (info->is_fun) {
				MccIdentifierConflictError *error = new MccIdentifierConflictError(var_name);
				error->m_line_no_cause_conflict = var->get_lineno();
				error->m_line_no_having_conflict = info->line_no;
				m_error_list.push_back(error);
				return;
			}
			
			// Same scope.
			if (info->scope == m_current_scope) {
				MccIdentifierConflictError *error = new MccIdentifierConflictError(var_name);
				error->m_line_no_cause_conflict = var->get_lineno();
				error->m_line_no_having_conflict = info->line_no;
				m_error_list.push_back(error);
				return;
			}
		}
	}
	
	// No conflict, add new information.
	info = new IdentifierInfo;
	info->id_name = var_name;
	info->line_no = var->get_lineno();
	info->scope = m_current_scope;
	info->is_fun = false;
	info->contain_fun_def = false;

	m_ids.push_back(info);
}

void MccIdentifierConflictChecker::detect(MccFunctionDeclaration *fun)
{
	if (!fun->contain_definition()) {
		return;
	}

	// When conflict happened on function id, stop to detect the variable
	// inside it.

	string fun_name = fun->get_decl_name();
	IdentifierInfo *new_func_info = nullptr;
	bool contain_def = fun->contain_definition();
	for (size_t i = 0, len = m_ids.size(); i < len; ++i) {
		IdentifierInfo *info = m_ids[i];
		if (info->id_name == fun_name) {
			if (info->is_fun) {
				// The function already had definition or current declaration
				// don't contain definition.
				if (info->contain_fun_def || !contain_def) {
					MccIdentifierConflictError *error = new MccIdentifierConflictError(fun_name);
					error->m_line_no_cause_conflict = fun->get_lineno();
					error->m_line_no_having_conflict = info->line_no;
					m_error_list.push_back(error);
					return;
				} else {
					info->contain_fun_def = true;
					new_func_info = info;
				}
			} else {
				// Already had a variable use the id.
				MccIdentifierConflictError *error = new MccIdentifierConflictError(fun_name);
				error->m_line_no_cause_conflict = fun->get_lineno();
				error->m_line_no_having_conflict = info->line_no;
				m_error_list.push_back(error);
				return;
			}

			break;
		}
	}
	
	// A new function.
	if (nullptr == new_func_info) {
		new_func_info = new IdentifierInfo;
		new_func_info->id_name = fun_name;
		new_func_info->is_fun = true;
		new_func_info->contain_fun_def = contain_def;
		new_func_info->line_no = fun->get_lineno();
		new_func_info->scope = m_current_scope;
		m_ids.push_back(new_func_info);
	}

	// Set scope to current function.
	m_current_scope = (void *) fun;

	// Check parameter.
	const vector<MccFuncParameter*> &param_list = fun->get_parameter_list();
	for (size_t i = 0, len = param_list.size(); i < len; ++i) {
		param_list[i]->semantic_detect();
	}

	// Check local variable in function.
	const vector<MccVariableDeclaration*> &local_decls 
		= fun->get_local_variable_decls();
	for (size_t i = 0, len = local_decls.size(); i < len; ++i) {
		local_decls[i]->semantic_detect();
	}

	// Exit function, return to global scope
	m_current_scope = nullptr;
}


void MccIdentifierConflictChecker::detect(MccFuncParameter *func_param)
{
	string param_name = func_param->m_name->m_name;
	IdentifierInfo *info = nullptr;
	for (size_t i = 0, len = m_ids.size(); i < len; ++i) {
		info = m_ids[i];
		if (info->id_name == param_name) {
			// The existent identifier is function.
			if (info->is_fun) {
				MccIdentifierConflictError *error = new MccIdentifierConflictError(param_name);
				error->m_line_no_cause_conflict = func_param->get_lineno();
				error->m_line_no_having_conflict = info->line_no;
				m_error_list.push_back(error);
				return;
			}

			// Same scope.
			if (info->scope == m_current_scope) {
				MccIdentifierConflictError *error = new MccIdentifierConflictError(param_name);
				error->m_line_no_cause_conflict = func_param->get_lineno();
				error->m_line_no_having_conflict = info->line_no;
				m_error_list.push_back(error);
				return;
			}
		}
	}

	// No conflict, add new information.
	info = new IdentifierInfo;
	info->id_name = param_name;
	info->line_no = func_param->get_lineno();
	info->scope = m_current_scope;
	info->is_fun = false;
	info->contain_fun_def = false;

	m_ids.push_back(info);
}
