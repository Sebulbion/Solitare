#ifndef STOCKSTACK_H
#define STOCKSTACK_H

#include <Windows.h>
#include "Stack.h"

class CStockStack : public ABStack
{
public:
	CStockStack();
	virtual ~CStockStack();

	// Inherited via IStack
	virtual bool TryPlace(ABStack * pStack) override;
	virtual ABStack * SplitStack(int _iIndex) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

	// Create a randomly shuffled deck of 52 cards
	static CStockStack* CreateFullDeck();

private:
	CStockStack(const CStockStack& _kr) = delete;
	CStockStack& operator= (const CStockStack& _kr) = delete;
};
#endif //STOCKSTACK_H
