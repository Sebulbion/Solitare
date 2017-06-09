#pragma once

#include "sprite.h"

class CCard
{
public:
	enum ESUIT 
	{
		HEARTS,
		DIAMONDS,
		CLUBS,
		SPADES,
		NO_SUIT
	};

	CCard(ESUIT, size_t _card_num);
	~CCard();

private:
	CSprite m_sprite;
};

