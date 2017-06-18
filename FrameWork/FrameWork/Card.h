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

	CCard(ESUIT, size_t _cardNum, bool _bIsRevealed);
	~CCard();

	int GetSuit();
	size_t GetCardNum();
	void Draw();
	void SetPos(const TPosition&);
	TPosition GetPos();
	void RevealCard();
	bool GetIsRevealed();

	static int GetCardWidth();
	static int GetCardHeight();

private:
	CSprite* m_pSpriteCardAtlas;
	CSprite* m_pSpriteCardBack;
	ESUIT m_eSuit;
	size_t m_cardNum;
	bool m_bIsRevealed;

	TPosition m_pos;

	static const int s_kiCardWidth;
	static const int s_kiCardHeight;

	CCard(const CCard& _kr) = delete;
	CCard& operator= (const CCard& _kr) = delete;
};

