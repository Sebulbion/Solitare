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

	CCard(ESUIT, size_t _cardNum);
	~CCard();

	int GetSuit();
	size_t GetCardNum();
	void DrawSection(int _iXFrames, int _iYFrames, int _iXFrameToDraw, int _iYFrameToDraw, int _iYOffset);
	void SetPos(const TPosition&);

private:
	CSprite* m_pSprite;
	ESUIT m_eSuit;
	size_t m_cardNum;

	CCard(const CCard& _kr) = delete;
	CCard& operator= (const CCard& _kr) = delete;
};

