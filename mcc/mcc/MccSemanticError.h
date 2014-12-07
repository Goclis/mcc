#pragma once
class MccSemanticError
{
public:
	MccSemanticError(void);
	virtual ~MccSemanticError(void);

	virtual void report() const;
};

