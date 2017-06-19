#pragma once

#include <Windows.h>
#include "Stack.h"

class CWasteStack : public ABStack
{
public:
	CWasteStack();
	virtual ~CWasteStack();

	// Inherited via IStack
	virtual bool TryPlace(ABStack * pStack) override;
	virtual ABStack * SplitStack(int _iIndex) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

	static const size_t s_kszNumWasteRevealed;

private:
	CWasteStack(const CWasteStack& _kr) = delete;
	CWasteStack& operator= (const CWasteStack& _kr) = delete;

	int m_iCardOffset;
};

