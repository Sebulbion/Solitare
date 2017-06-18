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
	CTableauStack* pStack = new CTableauStack();
	auto it = m_listpCards.begin();
	std::advance(it, _iIndex);

	if ((*it)->GetIsRevealed() == true)
	{
		it++;
		pStack->m_listpCards.splice(pStack->m_listpCards.begin(), m_listpCards, m_listpCards.begin(), it);
		pStack->SetPos(TPosition{ GetPos().x, GetPos().y + (m_iCardOffset * (int)m_listpCards.size()) });

		return pStack;
	}
	else
	{
		return nullptr;
	}
}

void CTableauStack::Draw()
{
	for (auto it = m_listpCards.rbegin(); it != m_listpCards.rend(); it++)
	{
		(*it)->DrawSection(13, 4, (*it)->GetCardNum(), (*it)->GetSuit());
	}
}

RECT CTableauStack::GetClickableArea()
{
	RECT recRect;

	recRect.left = GetPos().x;
	recRect.top = GetPos().y;
	if (m_listpCards.front()->GetIsRevealed())
	{
		recRect.right = GetPos().x + m_listpCards.front()->GetSprite()->GetWidth() / 13;
		recRect.bottom = GetPos().y + m_listpCards.front()->GetSprite()->GetHeight() / 4;
	}
	else
	{
		recRect.right = GetPos().x + m_listpCards.front()->GetSprite()->GetWidth();
		recRect.bottom = GetPos().y + m_listpCards.front()->GetSprite()->GetHeight();
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
			return m_listpCards.size() - 1 - i;
		}
	}
	return 0;
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
