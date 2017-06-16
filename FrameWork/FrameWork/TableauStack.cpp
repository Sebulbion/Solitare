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

IStack * CTableauStack::SplitStack()
{
	return nullptr;
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
	RECT rect;

	rect.left = GetPos().x;
	rect.top = GetPos().y;
	if (m_listpCards.front()->GetIsRevealed())
	{
		rect.right = GetPos().x + m_listpCards.front()->GetSprite()->GetWidth() / 13;
		rect.bottom = GetPos().y + m_listpCards.front()->GetSprite()->GetHeight() / 4;
	}
	else
	{
		rect.right = GetPos().x + m_listpCards.front()->GetSprite()->GetWidth();
		rect.bottom = GetPos().y + m_listpCards.front()->GetSprite()->GetHeight();
	}
	rect.bottom += m_iCardOffset * m_listpCards.size() - 1;

	return rect;
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
