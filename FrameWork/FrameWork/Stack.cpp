#include "Stack.h"
#include "Card.h"
#include "sprite.h"

ABStack::ABStack() :
	m_iWidth(CCard::GetCardWidth()),
	m_iHeight(CCard::GetCardHeight()),
	m_pos({ 0, 0 }),
	m_pEmptyCard(new CSprite())
{
}

void ABStack::SplitStackHelper(int _iIndex, ABStack *& _pStack)
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


ABStack::~ABStack()
{
	for (CCard* pCard : m_listpCards)
	{
		delete pCard;
	}
	delete m_pEmptyCard;
}

void ABStack::Draw()
{
	if (Empty())
	{
		m_pEmptyCard->Draw(m_pos, CCard::GetCardWidth(), CCard::GetCardHeight());
	}
	else
	{
		for (auto it = m_listpCards.rbegin(); it != m_listpCards.rend(); it++)
		{
			(*it)->Draw();
		}
	}
}

void ABStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;

	NotifyChange();
}

RECT ABStack::GetBoundingBox()
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

void ABStack::Place(ABStack * pStack)
{
	m_listpCards.splice(m_listpCards.begin(), pStack->m_listpCards, pStack->m_listpCards.begin(), pStack->m_listpCards.end());
}

TPosition ABStack::GetPos() const
{
	return m_pos;
}

int ABStack::GetWidth() const
{
	return m_iWidth;
}

int ABStack::GetHeight() const
{
	return m_iHeight;
}

int ABStack::GetSize() const
{
	return m_listpCards.size();
}

void ABStack::Push(CCard* const & _krpCard)
{
	m_listpCards.push_front(_krpCard);
	
	NotifyChange();
}

CCard*& ABStack::Top()
{
	return m_listpCards.front();
}

CCard *& ABStack::Bottom()
{
	return m_listpCards.back();
}

void ABStack::Pop()
{
	m_listpCards.pop_front();
}

bool ABStack::Empty()
{
	return m_listpCards.empty();
}
