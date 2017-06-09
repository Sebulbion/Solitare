#pragma once

#include "Stack.h"

class CTableauStack : public IStack
{
public:
	CTableauStack();
	virtual ~CTableauStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack() override;
	virtual void Draw() override;
};

