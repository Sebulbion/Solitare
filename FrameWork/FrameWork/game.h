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

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <array>

// Local Includes
#include "clock.h"
#include "Stack.h"
#include "WasteStack.h"
#include "StockStack.h"
#include "FoundationStack.h"
#include "TableauStack.h"

// Types

// Constants

// Prototypes
class CBackBuffer;

class CGame
{
    // Member Functions
public:
    ~CGame();

    bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

    void Draw();
    void Process(float _fDeltaTick);

	//TODO: Make generic for all stacks with the help of lance
	void SelectStack(IStack* _staStack, POINT _poiMousePos);

    void ExecuteOneFrame();

    CBackBuffer* GetBackBuffer();
    HINSTANCE GetAppInstance();
    HWND GetWindow();

    // Singleton Methods
    static CGame& GetInstance();
    static void DestroyInstance();

protected:

private:
    CGame();
    CGame(const CGame& _kr) = delete;
    CGame& operator= (const CGame& _kr) = delete;

    // Member Variables
	IStack* m_pStackGrabbed;

	CStockStack* m_pStockStack;
	CWasteStack* m_pWasteStack;
	std::array<CFoundationStack*, 4> m_arrpFoundationStacks;
	std::array<CTableauStack*, 7> m_arrpTableauStacks;

	static const int s_kiTableauStackSpacing;
	static const size_t s_kszNumTableauStacks;

public:

protected:
    CClock* m_pClock;

    CBackBuffer* m_pBackBuffer;

    //Application data
    HINSTANCE m_hApplicationInstance;
    HWND m_hMainWindow;

    // Singleton Instance
    static CGame* s_pGame;

private:

};

#endif    // __GAME_H__
