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
#include "Card.h"


// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;
const int CGame::s_kiTableauStackSpacing = 50;
const size_t CGame::s_kszNumTableauStacks = 7;
const size_t CGame::s_kszWastSize = 3;

// Static Function Prototypes
static POINT s_poiPreviousMousePos;

// Implementation

CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_pStackGrabbed(nullptr)
, m_pStockStack(new CStockStack)
, m_pWasteStack(new CWasteStack)
, m_bClicked(false)
, m_bClickReleased(false)
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
	m_pStockStack->SetPos({ s_kiTableauStackSpacing, 0 });

	m_pWasteStack->SetPos({ m_pStockStack->GetPos().x + m_pStockStack->GetWidth() + s_kiTableauStackSpacing, 0 });

	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{
			CCard* pCard = m_pStockStack->Top();
			m_pStockStack->Pop();
			m_arrpTableauStacks.at(i)->Push(pCard);
		}

		m_arrpTableauStacks.at(i)->SetPos({ s_kiTableauStackSpacing + i * (CCard::GetCardWidth() + s_kiTableauStackSpacing), CCard::GetCardHeight() + s_kiTableauStackSpacing });
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

	POINT poiMousePos;
	GetCursorPos(&poiMousePos);
	ScreenToClient(m_hMainWindow, &poiMousePos);

	if (m_bClicked && InsideRect(poiMousePos, m_pStockStack->GetClickableArea()))
	{
		for (size_t i = 0; i < s_kszWastSize; ++i)
		{
			CCard* pCard = m_pStockStack->Top();
			m_pStockStack->Pop();
			m_pWasteStack->Push(pCard);
			pCard->RevealCard();

			m_bClicked = false;
		}
	}

	//TODO: Change this temp movment
	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		SelectStack(m_arrpTableauStacks.at(i), poiMousePos);
	}

	if (m_pStackGrabbed != nullptr)
	{
		MoveGrabedStack(poiMousePos);
	}

	s_poiPreviousMousePos = poiMousePos;
}

void CGame::SelectStack(IStack * _staStack, POINT _poiMousePos)
{
	RECT stackRect = _staStack->GetClickableArea();

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// Check if the mouse is in the box of a stack
		if (_poiMousePos.x >= stackRect.left &&
			_poiMousePos.x <= stackRect.right &&
			_poiMousePos.y >= stackRect.top &&
			_poiMousePos.y <= stackRect.bottom)
		{
			if (m_bClicked == true)
			{
				m_pStackGrabbed = _staStack->SplitStack(_staStack->ClickedCardIndex(_poiMousePos));
			}
			/*test->SetPos({ stackRect.left + _poiMousePos.x - s_poiPreviousMousePos.x,
				stackRect.top + _poiMousePos.y - s_poiPreviousMousePos.y });*/

			/*_staStack->SetPos({ stackRect.left + _poiMousePos.x - s_poiPreviousMousePos.x,
				stackRect.top + _poiMousePos.y - s_poiPreviousMousePos.y });*/

			m_bClicked = false;
		}
	}
	
}

void CGame::MoveGrabedStack(POINT _poiMousePos)
{
	m_pStackGrabbed->SetPos({ m_pStackGrabbed->GetPos().x + _poiMousePos.x - s_poiPreviousMousePos.x,
		m_pStackGrabbed->GetPos().y + _poiMousePos.y - s_poiPreviousMousePos.y });

	/*if (s_bClickReleased == true)
	{
		m_pStackGrabbed->SetPos(ColidingStack(m_pStackGrabbed)->GetPos());
		m_pStackGrabbed = nullptr;
	}*/

	m_bClickReleased = false;
}

IStack * CGame::ColidingStack(IStack * pStack)
{
	RECT otherStackRect;
	RECT stackRect = pStack->GetClickableArea();
	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		otherStackRect = m_arrpTableauStacks.at(i)->GetClickableArea();

		if (stackRect.left < otherStackRect.right && stackRect.right > otherStackRect.left &&
			stackRect.top > otherStackRect.bottom && stackRect.bottom < otherStackRect.top)
		{
			return m_arrpTableauStacks.at(i);
		}
	}
	return nullptr;
}

void
CGame::ExecuteOneFrame()
{
    float fDT = m_pClock->GetDeltaTick();

	//TODO: Remove this temp if statment setting the top card to be revealed
	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		if (m_arrpTableauStacks.at(i)->Top()->GetIsRevealed() == false)
		{
			m_arrpTableauStacks.at(i)->Top()->RevealCard();
		}
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
