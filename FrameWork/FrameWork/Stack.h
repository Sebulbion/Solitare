#pragma once

#include <list>

#include "Position.h"
#include "Card.h"

class IStack
{
public:
	virtual ~IStack();

	// Try placing the specified stack onto this stack
	// This may fail due to stacking rules
	virtual bool TryPlace(IStack* pStack) = 0;

	// Split the stack into two separate stacks, 
	// return the top stack
	virtual IStack* SplitStack() = 0;

	// Draw the stack
	virtual void Draw() = 0;

	// Set the position of the top left corner of the stack
	virtual void SetPos(const TPosition&) = 0;
	
	// Get the position of the top left corner of the stack
	TPosition GetPos() const;

	// Get the width of the stack as laid out on the screen
	float GetWidth() const;

	// Get the height of the stack as laid out on the screen
	float GetHeight() const;

	void Push(const CCard&);
	CCard& Top();
	void Pop();

protected:
	IStack();

	// The dimensions of the stack when laid out on the screen
	float m_fWidth;
	float m_fHeight;

	// Top left corner position of the stack
	TPosition m_pos;

	std::list<CCard> m_listCards;
};

