//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: FoundationStack.h
// Description	: Foundation Stack header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#include "Stack.h"

class CFoundationStack : public ABStack
{
public:
	CFoundationStack();
	virtual ~CFoundationStack();

	// Inherited via IStack
	virtual bool TryPlace(ABStack * pStack) override;
	virtual ABStack * SplitStack(int _iIndex) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

private:
	CFoundationStack(const CFoundationStack& _kr) = delete;
	CFoundationStack& operator= (const CFoundationStack& _kr) = delete;
};

