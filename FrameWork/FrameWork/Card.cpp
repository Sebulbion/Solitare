#include "Card.h"
#include "resource.h"


CCard::CCard(ESUIT _eSuite, size_t _card_num) :
	m_sprite()
{
	m_sprite.Initialise(IDB_CARDATLAS, IDB_CARDATLASMASK);
}


CCard::~CCard()
{
}
