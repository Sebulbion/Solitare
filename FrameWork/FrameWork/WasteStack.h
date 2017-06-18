#pragma once

#include <Windows.h>
#include "Stack.h"

class CWasteStack : public IStack
{
public:
	CWasteStack();
	virtual ~CWasteStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack(int _iIndex) override;
	virtual void SetPos(const TPosition &) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;

private:
	CWasteStack(const CWasteStack& _kr) = delete;
	CWasteStack& operator= (const CWasteStack& _kr) = delete;

	int m_iCardOffset;
};

