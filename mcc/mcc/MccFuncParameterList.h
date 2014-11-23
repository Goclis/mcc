/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once

#include <vector>

class MccFuncParameter;

using std::vector;

class MccFuncParameterList
{
public:
	explicit MccFuncParameterList(MccFuncParameter *first);
	virtual ~MccFuncParameterList(void);

	/**
	 * @brief Same as vector::push_back.
	 */
	void push_back(MccFuncParameter *param);

	/**
	 * @brief Copy content to other list.
	 *
	 * @param list Destination list.
     */
	void copy_to_list(vector<MccFuncParameter *> &list);
	
private:
	vector<MccFuncParameter *> m_parameter_list;
};

