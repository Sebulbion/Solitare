#include "Stack.h"



IStack::IStack()
{
}


IStack::~IStack()
{
	for (CCard* pCard : m_listpCards)
	{
		delete pCard;
	}
}

TPosition IStack::GetPos() const
{
	return m_pos;
}

float IStack::GetWidth() const
{
	return m_fWidth;
}

float IStack::GetHeight() const
{
	return m_fHeight;
}

void IStack::Push(CCard* const & _krpCard)
{
	m_listpCards.push_front(_krpCard);
}

CCard*& IStack::Top()
{
	return m_listpCards.front();
}

void IStack::Pop()
{
	m_listpCards.pop_front();
}
