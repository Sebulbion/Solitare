#include <algorithm>
#include <vector>
#include <ctime>
#include <iterator>

#include "StockStack.h"
#include "Card.h"


CStockStack::CStockStack()
{
}


CStockStack::~CStockStack()
{
}

bool CStockStack::TryPlace(IStack * pStack)
{
	return false;
}

IStack * CStockStack::SplitStack()
{
	return nullptr;
}

void CStockStack::Draw()
{
}

CStockStack CStockStack::CreateFullDeck()
{
	CStockStack stockStack;
	std::vector<CCard> vecTempDeck;

	// Create an ordered vector of 52 cards
	for (int iSuit = 0; iSuit != CCard::ESUIT::NO_SUIT; ++iSuit)
	{
		CCard::ESUIT eSuit = static_cast<CCard::ESUIT>(iSuit);

		for (size_t szCardNum = 0; szCardNum < 13; ++szCardNum)
		{
			vecTempDeck.emplace_back(eSuit, szCardNum);
		}
	}

	// Shuffle the vector
	std::srand(unsigned(std::time(0)));
	std::random_shuffle(vecTempDeck.begin(), vecTempDeck.end());

	// Copyshuffled vector to stock stacks internal list
	std::copy(vecTempDeck.begin(), vecTempDeck.end(), std::back_inserter(stockStack.m_listCards));

	return stockStack;
}

void CStockStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
}
