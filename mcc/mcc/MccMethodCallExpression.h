/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#pragma once
#include "mccexpression.h"
#include <vector>

class MccIdentifier;
class MccExpressionList;

using std::vector;

class MccMethodCallExpression :
	public MccExpression
{
public:
	MccMethodCallExpression(MccIdentifier *id, MccExpressionList *expr_list);
	virtual ~MccMethodCallExpression(void);

	int generate_code() const;
	void semantic_detect();

	MccIdentifier *m_method_id;
	vector<MccExpression *> m_args;
};

