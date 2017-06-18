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

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Local Includes
#include "Position.h"

// Types

// Constants

// Prototypes
class CSprite
{
    // Member Functions
public:
    CSprite();
    ~CSprite();

    bool Initialise(int _iResourceID, int _iMaskResourceID);

    void Draw(const TPosition&);

	// Draws a section of a spritesheet
	void DrawSection(const TPosition&, int _iXFrames, int _iYFrames, int _iXFrameToDraw, int _iYFrameToDraw);
    void Process(float _fDeltaTick);

    int GetWidth() const;
    int GetHeight() const;

    void TranslateRelative(int _iX, int _iY);
    void TranslateAbsolute(int _iX, int _iY);

protected:
    HBITMAP m_hSprite;
    HBITMAP m_hMask;

    BITMAP m_bitmapSprite;
    BITMAP m_bitmapMask;

    static HDC s_hSharedSpriteDC;
    static int s_iRefCount;

private:
	CSprite(const CSprite& _kr) = delete;
	CSprite& operator= (const CSprite& _kr) = delete;
};

#endif    // __SPRITE_H__
