//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: TableauStack.h
// Description	: Tableau Stack header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#include <Windows.h>
#include "Stack.h"

class CTableauStack : public ABStack
{
public:
	CTableauStack();
	virtual ~CTableauStack();

	// Inherited via IStack
	virtual bool TryPlace(ABStack * pStack) override;
	virtual ABStack * SplitStack(int _iIndex) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

private:
	CTableauStack(const CTableauStack& _kr) = delete;
	CTableauStack& operator= (const CTableauStack& _kr) = delete;

	int m_iCardOffset;
};

