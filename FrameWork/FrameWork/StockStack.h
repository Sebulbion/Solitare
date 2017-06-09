#pragma once

#include "Stack.h"

class CStockStack : public IStack
{
public:
	CStockStack();
	virtual ~CStockStack();

	// Inherited via IStack
	virtual bool TryPlace(IStack * pStack) override;
	virtual IStack * SplitStack() override;
	virtual void SetPos(const TPosition &) override;
	virtual void Draw() override;

	// Create a randomly shuffled deck of 52 cards
	static CStockStack* CreateFullDeck();
};

