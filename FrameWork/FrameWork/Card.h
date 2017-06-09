#pragma once

#include "sprite.h"
#include "Position.h"

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

	void Draw();
	void SetPos(const TPosition&);

private:
	CSprite* m_pSprite;

	CCard(const CCard& _kr) = delete;
	CCard& operator= (const CCard& _kr) = delete;
};

