#include "Stack.h"
#include "Card.h"


IStack::IStack() :
	m_iWidth(CCard::GetCardWidth()),
	m_iHeight(CCard::GetCardHeight()),
	m_pos({ 0, 0 })
{
}


IStack::~IStack()
{
	for (CCard* pCard : m_listpCards)
	{
		delete pCard;
	}
}

void IStack::Draw()
{
	for (auto it = m_listpCards.rbegin(); it != m_listpCards.rend(); it++)
	{
		(*it)->Draw();
	}
}

RECT IStack::GetClickableArea()
{
	RECT recRect;

	recRect.left = GetPos().x;
	recRect.top = GetPos().y;

	if (m_listpCards.size() > 0)
	{
		CCard* pCard = m_listpCards.front();
		recRect.right = pCard->GetPos().x + pCard->GetCardWidth();
		recRect.bottom = pCard->GetPos().y + pCard->GetCardHeight();
	}
	else
	{
		recRect.right = GetPos().x + CCard::GetCardWidth();
		recRect.bottom = GetPos().y + CCard::GetCardHeight();
	}

	return recRect;
}

TPosition IStack::GetPos() const
{
	return m_pos;
}

int IStack::GetWidth() const
{
	return m_iWidth;
}

int IStack::GetHeight() const
{
	return m_iHeight;
}

void IStack::Push(CCard* const & _krpCard)
{
	m_listpCards.push_front(_krpCard);

	// Quick hack to update the position of the newly added card
	SetPos(m_pos);
}

CCard*& IStack::Top()
{
	return m_listpCards.front();
}

void IStack::Pop()
{
	m_listpCards.pop_front();
}
