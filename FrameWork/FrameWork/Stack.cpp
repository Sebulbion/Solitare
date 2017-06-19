#include "Stack.h"
#include "Card.h"


IStack::IStack() :
	m_iWidth(CCard::GetCardWidth()),
	m_iHeight(CCard::GetCardHeight()),
	m_pos({ 0, 0 })
{
}

void IStack::SplitStackHelper(int _iIndex, IStack *& _pStack)
{
	auto it = m_listpCards.begin();
	std::advance(it, _iIndex);

	if ((*it)->GetIsRevealed() == true)
	{
		it++;
		_pStack->m_listpCards.splice(_pStack->m_listpCards.begin(), m_listpCards, m_listpCards.begin(), it);
		_pStack->SetPos(_pStack->Bottom()->GetPos());
	}
	else
	{
		delete _pStack;
		_pStack = nullptr;
	}
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

void IStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;

	NotifyChange();
}

RECT IStack::GetBoundingBox()
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

void IStack::Place(IStack * pStack)
{
	m_listpCards.splice(m_listpCards.begin(), pStack->m_listpCards, pStack->m_listpCards.begin(), pStack->m_listpCards.end());
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

int IStack::GetSize() const
{
	return m_listpCards.size();
}

void IStack::Push(CCard* const & _krpCard)
{
	m_listpCards.push_front(_krpCard);
	
	NotifyChange();
}

CCard*& IStack::Top()
{
	return m_listpCards.front();
}

CCard *& IStack::Bottom()
{
	return m_listpCards.back();
}

void IStack::Pop()
{
	m_listpCards.pop_front();
}

bool IStack::Empty()
{
	return m_listpCards.empty();
}
