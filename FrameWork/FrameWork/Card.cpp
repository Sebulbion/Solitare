#include "Card.h"
#include "resource.h"


CCard::CCard(ESUIT _eSuite, size_t _card_num) :
	m_pSprite(new CSprite())
{
	m_pSprite->Initialise(IDB_CARDATLAS, IDB_CARDATLASMASK);
}


CCard::~CCard()
{
	delete m_pSprite;
}

void CCard::Draw()
{
	m_pSprite->Draw();
}

void CCard::SetPos(const TPosition& _krpos)
{
	m_pSprite->SetX(_krpos.x);
	m_pSprite->SetY(_krpos.y);
}
