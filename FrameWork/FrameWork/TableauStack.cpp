#include "TableauStack.h"



CTableauStack::CTableauStack():
	m_iCardOffset(20)
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
	int i = 0;
	for (CCard* pCard : m_listpCards)
	{
		pCard->DrawSection(13,4,pCard->GetCardNum(), pCard->GetSuit(), i * m_iCardOffset);
		++i;
	}
}

void CTableauStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
	for (CCard* pCard : m_listpCards)
	{
		pCard->SetPos(m_pos);
	}
}
