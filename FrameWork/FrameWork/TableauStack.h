#pragma once

#include <Windows.h>
#include "Stack.h"

class CTableauStack : public IStack
{
public:
	CTableauStack();
	virtual ~CTableauStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack(int _iIndex) override;
	virtual void SetPos(const TPosition &) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;

private:
	CTableauStack(const CTableauStack& _kr) = delete;
	CTableauStack& operator= (const CTableauStack& _kr) = delete;

	int m_iCardOffset;
};

