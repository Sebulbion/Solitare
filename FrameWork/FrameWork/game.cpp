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
    VALIDATE(m_pClock ->Initialise());
    m_pClock->Process();

    m_pBackBuffer = new CBackBuffer();
    VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pStockStack = CStockStack::CreateFullDeck();
	m_pStockStack->SetPos({ 0, 0 });

	CCard* pCard = m_pStockStack->Top();
	m_pStockStack->Pop();
	m_arrpTableauStacks.at(0)->Push(pCard);
	m_arrpTableauStacks.at(0)->SetPos({ 0, 0 });

    return (true);
}

void
CGame::Draw()
{
    m_pBackBuffer->Clear();

	if (m_pStackGrabbed)
	{
		m_pStackGrabbed->Draw();
	}
	
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

    m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
    // Process all the game’s logic here.
	//Load a new sprite.
	
}

void 
CGame::ExecuteOneFrame()
{
    float fDT = m_pClock->GetDeltaTick();

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
