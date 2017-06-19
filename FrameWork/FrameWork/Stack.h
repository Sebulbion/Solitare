#pragma once

#include <Windows.h>
#include <list>

#include "Position.h"

class CSprite;

class CCard;

class ABStack
{
public:
	virtual ~ABStack();

	// Try placing the specified stack onto this stack
	// This may fail due to stacking rules
	virtual bool TryPlace(ABStack* pStack) = 0;

	// Plases a stack onto another stack
	void Place(ABStack* pStack);

	// Split the stack into two separate stacks, 
	// return the top stack
	virtual ABStack* SplitStack(int _iIndex) = 0;

	// Draw the stack
	virtual void Draw();

	// Returns the box of the stack
	virtual RECT GetBoundingBox();

	// Returns the index of the card you clicked in the stack
	virtual int ClickedCardIndex(POINT _poiMousePos) = 0;

	// Notify the stack of any changes that have been made to it 
	// (should be called to reveal top cards)
	virtual void NotifyChange() = 0;
	
	// Set the position of the top left corner of the stack
	void SetPos(const TPosition&);
	
	// Get the position of the top left corner of the stack
	TPosition GetPos() const;

	// Get the width of the stack as laid out on the screen
	int GetWidth() const;

	// Get the height of the stack as laid out on the screen
	int GetHeight() const;

	// Get the number of cards in the stack
	int GetSize() const;

	void Push(CCard* const &);
	CCard*& Top();
	CCard*& Bottom();
	void Pop();
	bool Empty();

protected:
	ABStack();
	ABStack(const ABStack& _kr) = delete;
	ABStack& operator= (const ABStack& _kr) = delete;

	// A Helper function for splitting stacks
	// Returns the top stack into the supplied stack pointer
	void SplitStackHelper(int _iIndex, ABStack*& _pStack);

	// The dimensions of the stack when laid out on the screen
	int m_iWidth;
	int m_iHeight;

	// Top left corner position of the stack
	TPosition m_pos;

	std::list<CCard*> m_listpCards;
	CSprite* m_pEmptyCard;
};

