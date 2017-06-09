#pragma once

#include "Stack.h"

class CWasteStack : public IStack
{
public:
	CWasteStack();
	virtual ~CWasteStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack() override;
	virtual void Draw() override;
};

