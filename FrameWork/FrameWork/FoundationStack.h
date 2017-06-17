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
	virtual void SetPos(const TPosition &) override;
	virtual void Draw() override;
	virtual RECT GetClickableArea() override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;

private:
	CFoundationStack(const CFoundationStack& _kr) = delete;
	CFoundationStack& operator= (const CFoundationStack& _kr) = delete;
};

