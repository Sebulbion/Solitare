#include "WasteStack.h"
#include "Card.h"


CWasteStack::CWasteStack() :
	IStack(),
	m_iCardOffset(40)
{
}


CWasteStack::~CWasteStack()
{
}

bool CWasteStack::TryPlace(IStack * pStack)
{
	return false;
}

IStack * CWasteStack::SplitStack(int _iIndex)
{
	return nullptr;
}

int CWasteStack::ClickedCardIndex(POINT _poiMousePos)
{
	return 0;
}

void CWasteStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
	int i = 0;
	for (auto it = m_listpCards.rbegin(); it != m_listpCards.rend(); it++)
	{
		(*it)->SetPos({ m_pos.x, m_pos.y });
		++i;
	}

	i = 2;
	for (auto it = m_listpCards.begin(); it != m_listpCards.end() && i >= 0; it++)
	{
		(*it)->SetPos({ m_pos.x + i * m_iCardOffset, m_pos.y });
		--i;
	}
}
