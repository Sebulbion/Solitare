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
