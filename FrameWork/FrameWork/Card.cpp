#include "Card.h"
#include "resource.h"

const int CCard::s_kiCardWidth = 168;
const int CCard::s_kiCardHeight = 234;

CCard::CCard(ESUIT _eSuite, size_t _cardNum, bool _bIsRevealed) :
	m_pSpriteCardAtlas(new CSprite()),
	m_pSpriteCardBack(new CSprite()),
	m_eSuit(_eSuite),
	m_cardNum(_cardNum),
	m_bIsRevealed(_bIsRevealed)
{
	m_pSpriteCardAtlas->Initialise(IDB_CARDATLAS, IDB_BITMAP2);
	m_pSpriteCardBack->Initialise(IDB_BITMAP3, IDB_BITMAP1);
}


CCard::~CCard()
{
	delete m_pSpriteCardAtlas;
	delete m_pSpriteCardBack;
}

int CCard::GetSuit()
{
	return m_eSuit;
}

size_t CCard::GetCardNum()
{
	return m_cardNum;
}

void CCard::Draw()
{
	if (m_bIsRevealed)
	{
		m_pSpriteCardAtlas->DrawSection(m_pos, 13, 4, m_cardNum, static_cast<int>(m_eSuit));
	}
	else
	{
		m_pSpriteCardBack->Draw(m_pos);
	}
}

void CCard::SetPos(const TPosition& _krpos)
{
	m_pos = _krpos;
}

TPosition CCard::GetPos()
{
	return m_pos;
}

void CCard::RevealCard()
{
	m_bIsRevealed = true;
}

bool CCard::GetIsRevealed()
{
	return m_bIsRevealed;
}

int CCard::GetCardWidth()
{
	return s_kiCardWidth;
}

int CCard::GetCardHeight()
{
	return s_kiCardHeight;
}
