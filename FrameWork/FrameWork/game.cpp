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
#include "Clock.h"
#include "BackBuffer.h"
#include "utils.h"
#include "sprite.h"


// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;
const int CGame::s_kiTableauStackSpacing = 50;
const size_t CGame::s_kszNumTableauStacks = 7;

// Static Function Prototypes

// Implementation

CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_pStackGrabbed(nullptr)
, m_pStockStack(new CStockStack)
, m_pWasteStack(new CWasteStack)
{
	for (CTableauStack*& rpTableauStack : m_arrpTableauStacks)
	{
		rpTableauStack = new CTableauStack;
	}
	for (CFoundationStack*& rpFoundationStack : m_arrpFoundationStacks)
	{
		rpFoundationStack = new CFoundationStack;
	}
}

CGame::~CGame()
{
    delete m_pBackBuffer;
    m_pBackBuffer = 0;

    delete m_pClock;
    m_pClock = 0;

	// Delete stacks
	if (m_pStackGrabbed)
		delete m_pStackGrabbed;
	if (m_pStockStack)
		delete m_pStockStack;
	if (m_pWasteStack)
		delete m_pWasteStack;
	for (CTableauStack*& rpTableauStack : m_arrpTableauStacks)
	{
		if (rpTableauStack)
			delete rpTableauStack;
	}
	for (CFoundationStack*& rpFoundationStack : m_arrpFoundationStacks)
	{
		if (rpFoundationStack)
			delete rpFoundationStack;
	}
}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pStockStack = CStockStack::CreateFullDeck();
	m_pStockStack->SetPos({ 0, 0 });

	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{
			CCard* pCard = m_pStockStack->Top();
			m_pStockStack->Pop();
			m_arrpTableauStacks.at(i)->Push(pCard);
		}

		m_arrpTableauStacks.at(i)->SetPos({ i * (CCard::GetCardWidth() + s_kiTableauStackSpacing), 0 });
	}

    return (true);
}

void
CGame::Draw()
{
    m_pBackBuffer->Clear();
	
	m_pStockStack->Draw();
	m_pWasteStack->Draw();
	for (CFoundationStack*& rpFoundationStack: m_arrpFoundationStacks)
	{
		rpFoundationStack->Draw();
	}
	for (CTableauStack*& rpTableauStack : m_arrpTableauStacks)
	{
		rpTableauStack->Draw();
	}

	if (m_pStackGrabbed)
	{
		m_pStackGrabbed->Draw();
	}

    m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
    // Process all the game’s logic here.
	//Load a new sprite.

	//TODO: Remove this temp movment
	POINT mousePos;
	static POINT s_previousMousePos;
	RECT windowRect;
	GetWindowRect(GetWindow(), &windowRect);
	if (GetCursorPos(&mousePos))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			RECT stackRect = m_arrpTableauStacks.at(0)->GetClickableArea();

			// Magic numbers for the borders
			if (mousePos.x - windowRect.left - 10 >= stackRect.left &&
				mousePos.x - windowRect.left - 5 <= stackRect.right &&
				mousePos.y - windowRect.top - 35 >= stackRect.top &&
				mousePos.y - windowRect.top + 15 <= stackRect.bottom)
			{
				m_arrpTableauStacks.at(0)->SetPos({ stackRect.left + mousePos.x - s_previousMousePos.x,
					stackRect.top + mousePos.y - s_previousMousePos.y});
			}
		}
	}
	s_previousMousePos = mousePos;
	
}

void 
CGame::ExecuteOneFrame()
{
    float fDT = m_pClock->GetDeltaTick();

	//TODO: Remove this temp if statment setting the top card to be revealed
	if (m_arrpTableauStacks.at(0)->Top()->GetIsRevealed() == false)
	{
		m_arrpTableauStacks.at(0)->Top()->RevealCard();
	}

    Process(fDT);
    Draw();

    m_pClock->Process();

    Sleep(1);
}

CGame&
CGame::GetInstance()
{
    if (s_pGame == 0)
    {
        s_pGame = new CGame();
    }

    return (*s_pGame);
}

void 
CGame::DestroyInstance()
{
    delete s_pGame;
    s_pGame = 0;
}

CBackBuffer* 
CGame::GetBackBuffer()
{
    return (m_pBackBuffer);
}

HINSTANCE 
CGame::GetAppInstance()
{
    return (m_hApplicationInstance);
}

HWND 
CGame::GetWindow()
{
    return (m_hMainWindow);
}
