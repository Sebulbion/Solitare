#pragma once

#include <Windows.h>
#include "Stack.h"

class CStockStack : public IStack
{
public:
	CStockStack();
	virtual ~CStockStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack(int _iIndex) override;
	virtual void Draw() override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

	// Create a randomly shuffled deck of 52 cards
	static CStockStack* CreateFullDeck();

private:
	CStockStack(const CStockStack& _kr) = delete;
	CStockStack& operator= (const CStockStack& _kr) = delete;
};

