#include "FoundationStack.h"
#include "Card.h"



CFoundationStack::CFoundationStack() :
	ABStack()
{
}


CFoundationStack::~CFoundationStack()
{
}

bool CFoundationStack::TryPlace(ABStack * pStack)
{
	if (pStack->GetSize() == 1)
	{
		if (m_listpCards.size() == 0)
		{
			if (pStack->Bottom()->GetCardNum() == 0)
			{
				// Combine stacks
				Place(pStack);
				return true;
			}
		}
		else
		{
			if ((*m_listpCards.begin())->GetCardNum() == pStack->Bottom()->GetCardNum() - 1)
			{
				if ((*m_listpCards.begin())->GetSuit() == pStack->Bottom()->GetSuit())
				{
					// Combine Stacks
					Place(pStack);
					return true;
				}
			}
		}
	}
	return false;
}

ABStack * CFoundationStack::SplitStack(int _iIndex)
{
	ABStack* pStack = new CFoundationStack();
	SplitStackHelper(_iIndex, pStack);

	return pStack;
}

int CFoundationStack::ClickedCardIndex(POINT _poiMousePos)
{
	return (m_listpCards.size() - 1);
}

void CFoundationStack::NotifyChange()
{
	for (auto it = m_listpCards.rbegin(); it != m_listpCards.rend(); it++)
	{
		(*it)->SetPos (m_pos);
	}

	// Keep top cards revealed
	if (!m_listpCards.empty())
	{
		m_listpCards.front()->RevealCard();
	}
}
