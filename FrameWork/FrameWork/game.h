//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: game.h
// Description	: Game header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <array>
#include <vector>

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

	bool SelectStack(ABStack* _staStack, POINT _poiMousePos);
	void MoveGrabbedStack(POINT _poiMousePos);
	void PlaceGrabbedStack(POINT _poiMousePos);
	void HandleClick();
	void HandleClickRelease();

	// Make the stock only pop 1 card into the waste at a time
	// Reverts back to default (3 cards) if already in easy mode
	void ToggleEasyMode();

	// Returns true when the game is set to only pop 1 card from the stock at a time
	bool IsEasyMode();

	// Returns a stack that the input stack collides with
	std::vector<ABStack*> ColidingStack(ABStack* pStack);

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

	bool CheckWinCondition();

    // Member Variables
	ABStack* m_pStackGrabbed;
	ABStack* m_pStackGrabbedFromStack;

	CStockStack* m_pStockStack;
	CWasteStack* m_pWasteStack;
	std::array<CFoundationStack*, 4> m_arrpFoundationStacks;
	std::array<CTableauStack*, 7> m_arrpTableauStacks;

	size_t m_szNumToPopFromStock;

	static const int s_kiStackSpacing;
	static const size_t s_kszNumTableauStacks;
	static const size_t s_kszNumFoundationStacks;
	static const size_t s_kszDefaultNumToPopFromStock;

public:
	bool m_bClickToHandle;
	bool m_bClickReleaseToHandle;

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
