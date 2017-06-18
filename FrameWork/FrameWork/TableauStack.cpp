#include "TableauStack.h"



CTableauStack::CTableauStack():
	m_iCardOffset(40)
{
}


CTableauStack::~CTableauStack()
{
}

bool CTableauStack::TryPlace(IStack * pStack)
{
	return false;
}

IStack * CTableauStack::SplitStack(int _iIndex)
{
	CTableauStack* pstaStack = new CTableauStack();
	auto it = m_listpCards.begin();
	std::advance(it, _iIndex);

	pstaStack->m_listpCards.splice(pstaStack->m_listpCards.begin(), m_listpCards, it);

	return pstaStack;
}

void CTableauStack::Draw()
{
	for (auto it = m_listpCards.rbegin(); it != m_listpCards.rend(); it++)
	{
		(*it)->Draw();
	}
}

RECT CTableauStack::GetClickableArea()
{
	RECT recRect;

	recRect.left = GetPos().x;
	recRect.top = GetPos().y;
	if (m_listpCards.front()->GetIsRevealed())
	{
		recRect.right = GetPos().x + CCard::GetCardWidth();
		recRect.bottom = GetPos().y + CCard::GetCardHeight();
	}
	else
	{
		recRect.right = GetPos().x + CCard::GetCardWidth();
		recRect.bottom = GetPos().y + CCard::GetCardHeight();
	}
	recRect.bottom += m_iCardOffset * (m_listpCards.size() - 1);

	return recRect;
}

int CTableauStack::ClickedCardIndex(POINT _poiMousePos)
{
	for (int i = 0; i < (m_listpCards.size() - 1); ++i)
	{
		if (_poiMousePos.y <= GetPos().y + ((i + 1) * m_iCardOffset))
		{
			return m_listpCards.size() - i;
		}
	}
	return (0);
}

void CTableauStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
	int i = 0;
	for (auto it = m_listpCards.rbegin(); it != m_listpCards.rend(); it++)
	{
		(*it)->SetPos({ m_pos.x, m_pos.y + i * m_iCardOffset });
		++i;
	}
}
