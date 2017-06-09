#include "TableauStack.h"



CTableauStack::CTableauStack()
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
	for (CCard* pCard : m_listpCards)
	{
		pCard->Draw();
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
