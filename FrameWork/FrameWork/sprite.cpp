//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

// Static Function Prototypes

// Implementation

CSprite::CSprite()
{
    ++s_iRefCount;
}

CSprite::~CSprite()
{
    DeleteObject(m_hSprite);
    DeleteObject(m_hMask);

    --s_iRefCount;

    if (s_iRefCount == 0)
    {
        DeleteDC(s_hSharedSpriteDC);
        s_hSharedSpriteDC =  0;
    }
}

bool
CSprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID)
{
    HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

    if (!s_hSharedSpriteDC)
    {
        s_hSharedSpriteDC = CreateCompatibleDC(NULL);
    }

    m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));
    VALIDATE(m_hSprite);
    m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
    VALIDATE(m_hMask);

    GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
    GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

    return (true);
}

void
CSprite::Draw(const TPosition& _krpos, int _iWidth, int _iHeight)
{
    int iW = GetWidth();
    int iH = GetHeight();

    int iX = _krpos.x;
    int iY = _krpos.y;

    CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

    StretchBlt(pBackBuffer->GetBFDC(), iX, iY, _iWidth, _iHeight, s_hSharedSpriteDC, 0, 0, iW, iH, SRCAND);

    SelectObject(s_hSharedSpriteDC, m_hSprite);

	StretchBlt(pBackBuffer->GetBFDC(), iX, iY, _iWidth, _iHeight, s_hSharedSpriteDC, 0, 0, iW, iH, SRCPAINT);

    SelectObject(s_hSharedSpriteDC, hOldObj);
}

void CSprite::DrawSection(const TPosition& _krpos, int _iWidth, int _iHeight, int _iXFrames, int _iYFrames, int _iXFrameToDraw,int _iYFrameToDraw)
{
	int iW = GetWidth() / _iXFrames;
	int iH = GetHeight() / _iYFrames;

	int iX = _krpos.x;
	int iY = _krpos.y;

	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	StretchBlt(pBackBuffer->GetBFDC(),
		iX, 
		iY, 
		_iWidth,
		_iHeight,
		s_hSharedSpriteDC, 
		iW * _iXFrameToDraw,
		iH * _iYFrameToDraw,
		iW,
		iH,
		SRCAND);

	SelectObject(s_hSharedSpriteDC, m_hSprite);

	StretchBlt(pBackBuffer->GetBFDC(),
		iX,
		iY,
		_iWidth,
		_iHeight,
		s_hSharedSpriteDC, 
		iW * _iXFrameToDraw, 
		iH * _iYFrameToDraw,
		iW,
		iH,
		SRCPAINT);

	SelectObject(s_hSharedSpriteDC, hOldObj);
}

void
CSprite::Process(float _fDeltaTick)
{

}

int
CSprite::GetWidth() const
{
    return (m_bitmapSprite.bmWidth);
}

int
CSprite::GetHeight() const
{
    return (m_bitmapSprite.bmHeight);
}