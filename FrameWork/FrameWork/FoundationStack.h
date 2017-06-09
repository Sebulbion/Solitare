#pragma once

#include "Stack.h"

class CFoundationStack : public IStack
{
public:
	CFoundationStack();
	virtual ~CFoundationStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack() override;
	virtual void Draw() override;
};

