//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: StockStack.h
// Description	: Stock Stack header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once
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
