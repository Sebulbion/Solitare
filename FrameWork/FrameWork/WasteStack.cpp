#include "WasteStack.h"
#include "Card.h"
#include "utils.h"

const size_t CWasteStack::s_kszNumWasteRevealed = 3;

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
	IStack* pStack = new CWasteStack();
	SplitStackHelper(_iIndex, pStack);

	return pStack;
}

int CWasteStack::ClickedCardIndex(POINT _poiMousePos)
{
	for (int i = 0; i < s_kszNumWasteRevealed - 1; ++i)
	{
		if (_poiMousePos.x <= GetPos().x + ((i + 1) * m_iCardOffset))
		{
			return s_kszNumWasteRevealed - 1 - i;
		}
	}
	return 0;
}

void CWasteStack::NotifyChange()
{
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
