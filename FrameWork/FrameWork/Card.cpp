#include "Card.h"
#include "resource.h"


CCard::CCard(ESUIT _eSuite, size_t _card_num)
{
	m_sprite.Initialise(IDB_CARDATLAS, IDB_CARDATLASMASK);
}


CCard::~CCard()
{
}

void CCard::Draw()
{
	m_sprite.Draw();
}

void CCard::SetPos(const TPosition& _krpos)
{
	m_sprite.SetX(_krpos.x);
	m_sprite.SetY(_krpos.y);
}
