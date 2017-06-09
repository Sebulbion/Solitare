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
	virtual void SetPos(const TPosition &) override;
	virtual void Draw() override;

private:
	CFoundationStack(const CFoundationStack& _kr) = delete;
	CFoundationStack& operator= (const CFoundationStack& _kr) = delete;
};

