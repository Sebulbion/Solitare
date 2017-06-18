#pragma once

#include <Windows.h>
#include <list>

#include "Position.h"

class CCard;

class IStack
{
public:
	virtual ~IStack();

	// Try placing the specified stack onto this stack
	// This may fail due to stacking rules
	virtual bool TryPlace(IStack* pStack) = 0;

	// Split the stack into two separate stacks, 
	// return the top stack
	virtual IStack* SplitStack(int _iIndex) = 0;

	// Draw the stack
	virtual void Draw();

	// Set the position of the top left corner of the stack
	virtual void SetPos(const TPosition&) = 0;

	// Returns the box of the stack
	virtual RECT GetClickableArea();

	// Returns the index of the card you clicked in the stack
	virtual int ClickedCardIndex(POINT _poiMousePos) = 0;
	
	// Get the position of the top left corner of the stack
	TPosition GetPos() const;

	// Get the width of the stack as laid out on the screen
	int GetWidth() const;

	// Get the height of the stack as laid out on the screen
	int GetHeight() const;

	void Push(CCard* const &);
	CCard*& Top();
	void Pop();

protected:
	IStack();
	IStack(const IStack& _kr) = delete;
	IStack& operator= (const IStack& _kr) = delete;

	// The dimensions of the stack when laid out on the screen
	int m_iWidth;
	int m_iHeight;

	// Top left corner position of the stack
	TPosition m_pos;

	std::list<CCard*> m_listpCards;
};

