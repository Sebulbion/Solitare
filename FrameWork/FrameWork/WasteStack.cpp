#include "WasteStack.h"
#include "TableauStack.h"
#include "Card.h"
#include "utils.h"
#include "resource.h"
#include "sprite.h"

const size_t CWasteStack::s_kszNumWasteRevealed = 3;

CWasteStack::CWasteStack() :
	ABStack(),
	m_iCardOffset(40)
{
	m_pEmptyCard->Initialise(IDB_BITMAP4, IDB_BITMAP1);
}


CWasteStack::~CWasteStack()
{
}

bool CWasteStack::TryPlace(ABStack * pStack)
{
	return false;
}

ABStack * CWasteStack::SplitStack(int _iIndex)
{
	// Only the top card can be split off a waste stack
	if (_iIndex != 0)
	{
		return nullptr;
	}

	ABStack* pStack = new CTableauStack();
	SplitStackHelper(_iIndex, pStack);

	return pStack;
}

int CWasteStack::ClickedCardIndex(POINT _poiMousePos)
{
	for (int i = 0; i < s_kszNumWasteRevealed - 1 && i < GetSize() - 1; ++i)
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
		int iDistToEnd = m_listpCards.size() - i;
		if (iDistToEnd < s_kszNumWasteRevealed)
		{
			int iOffsetIdx;
			if (m_listpCards.size() < s_kszNumWasteRevealed)
			{
				iOffsetIdx = i;
			}
			else
			{
				iOffsetIdx = s_kszNumWasteRevealed - iDistToEnd;
			}
			(*it)->SetPos({ m_pos.x + iOffsetIdx * m_iCardOffset, m_pos.y });
		}
		else
		{
			(*it)->SetPos({ m_pos.x, m_pos.y });
		}

		++i;
	}

}
