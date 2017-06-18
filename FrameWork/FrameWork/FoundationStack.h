#pragma once

#include "Stack.h"

class CFoundationStack : public IStack
{
public:
	CFoundationStack();
	virtual ~CFoundationStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack(int _iIndex) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

private:
	CFoundationStack(const CFoundationStack& _kr) = delete;
	CFoundationStack& operator= (const CFoundationStack& _kr) = delete;
};

