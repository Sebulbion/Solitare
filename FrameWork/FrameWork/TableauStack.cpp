#include "TableauStack.h"
#include "Card.h"


CTableauStack::CTableauStack():
	IStack(),
	m_iCardOffset(40)
{
}


CTableauStack::~CTableauStack()
{
}

bool CTableauStack::TryPlace(IStack * pStack)
{
	if (m_listpCards.size() == 0)
	{
		if (pStack->Top()->GetCardNum() == 12)
		{
			// Combine stacks
			Place(pStack);
			return true;
		}
	}
	else
	{
		if ((*m_listpCards.begin())->GetCardNum() == pStack->Top()->GetCardNum() + 1)
		{
			if ((*m_listpCards.begin())->GetSuit() / 2 != pStack->Top()->GetSuit() / 2)
			{
				// Combine Stacks
				Place(pStack);
				return true;
			}
		}
	}
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
