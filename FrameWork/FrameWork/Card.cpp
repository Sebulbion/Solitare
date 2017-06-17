#include "Card.h"
#include "resource.h"

const int CCard::s_kiCardWidth = 168;
const int CCard::s_kiCardHeight = 234;

CCard::CCard(ESUIT _eSuite, size_t _cardNum, bool _bIsRevealed) :
	m_pSprite(new CSprite()),
	m_eSuit(_eSuite),
	m_cardNum(_cardNum),
	m_bIsRevealed(_bIsRevealed)
{
	if (m_bIsRevealed)
	{
		m_pSprite->Initialise(IDB_CARDATLAS, IDB_BITMAP2);
	}
	else
	{
		m_pSprite->Initialise(IDB_BITMAP3, IDB_BITMAP1);
	}
}


CCard::~CCard()
{
	delete m_pSprite;
}

int CCard::GetSuit()
{
	return m_eSuit;
}

size_t CCard::GetCardNum()
{
	return m_cardNum;
}

void CCard::DrawSection(int _iXFrames, int _iYFrames, int _iXFrameToDraw, int _iYFrameToDraw)
{
	if (m_bIsRevealed)
	{
		m_pSprite->DrawSection(_iXFrames, _iYFrames, _iXFrameToDraw, _iYFrameToDraw);
	}
	else
	{
		m_pSprite->Draw();
	}
}

void CCard::SetPos(const TPosition& _krpos)
{
	m_pSprite->SetX(_krpos.x);
	m_pSprite->SetY(_krpos.y);
}

TPosition CCard::GetPos()
{
	return{ m_pSprite->GetX(), m_pSprite->GetY() };
}

void CCard::RevealCard()
{
	m_bIsRevealed = true;
	m_pSprite->Initialise(IDB_CARDATLAS, IDB_BITMAP2);
}

bool CCard::GetIsRevealed()
{
	return m_bIsRevealed;
}

CSprite * CCard::GetSprite()
{
	return m_pSprite;
}

int CCard::GetCardWidth()
{
	return s_kiCardWidth;
}

int CCard::GetCardHeight()
{
	return s_kiCardHeight;
}
