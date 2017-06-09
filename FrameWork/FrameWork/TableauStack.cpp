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
	for (CCard& rCard : m_listCards)
	{
		rCard.Draw();
	}
}

void CTableauStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
	for (CCard& rCard : m_listCards)
	{
		rCard.SetPos(m_pos);
	}
}
