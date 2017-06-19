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
const int CGame::s_kiStackSpacing = 50;
const size_t CGame::s_kszNumTableauStacks = 7;
const size_t CGame::s_kszNumFoundationStacks = 4;

// Static Function Prototypes
static POINT s_poiPreviousMousePos;
static POINT s_poiMousePos;

// Implementation

CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_pStackGrabbed(nullptr)
, m_bClickToHandle(false)
, m_bClickReleaseToHandle(false)
{
	
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

	m_pStockStack = new CStockStack;
	m_pWasteStack = new CWasteStack;

	for (CTableauStack*& rpTableauStack : m_arrpTableauStacks)
	{
		rpTableauStack = new CTableauStack;
	}
	for (CFoundationStack*& rpFoundationStack : m_arrpFoundationStacks)
	{
		rpFoundationStack = new CFoundationStack;
	}

	// Init and place stacks
	m_pStockStack = CStockStack::CreateFullDeck();
	m_pStockStack->SetPos({ s_kiStackSpacing, 0 });
	m_pWasteStack->SetPos({ m_pStockStack->GetPos().x + m_pStockStack->GetWidth() + s_kiStackSpacing, 0 });

	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		m_arrpTableauStacks.at(i)->SetPos({ s_kiStackSpacing + i * (CCard::GetCardWidth() + s_kiStackSpacing), CCard::GetCardHeight() + s_kiStackSpacing });

		for (int j = 0; j < i + 1; ++j)
		{
			CCard* pCard = m_pStockStack->Top();
			m_pStockStack->Pop();
			m_arrpTableauStacks.at(i)->Push(pCard);
			pCard->HideCard();
		}

		m_arrpTableauStacks.at(i)->Top()->RevealCard();
	}

	for (int i = 0; i < s_kszNumFoundationStacks; ++i)
	{
		m_arrpFoundationStacks.at(i)->SetPos({ 3 * CCard::GetCardWidth() + 4 * s_kiStackSpacing + i *
			(CCard::GetCardWidth() + s_kiStackSpacing), 0 });
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

	GetCursorPos(&s_poiMousePos);
	ScreenToClient(m_hMainWindow, &s_poiMousePos);

	if (m_bClickToHandle)
	{
		HandleClick();
	}

	// Handle movement of grabbed stack
	if (m_pStackGrabbed != nullptr)
	{
		MoveGrabbedStack(s_poiMousePos);
	}

	// Handle click release
	if (m_bClickReleaseToHandle)
	{
		HandleClickRelease();
	}

	s_poiPreviousMousePos = s_poiMousePos;
}

bool CGame::SelectStack(ABStack * _staStack, POINT _poiMousePos)
{
	// Make sure there is nothing already grabbed
	if (m_pStackGrabbed != nullptr)
	{
		PlaceGrabbedStack(_poiMousePos);
	}

	RECT stackBoundingBox = _staStack->GetBoundingBox();

	// Check if the mouse is in the bounding box of a stack
	if (InsideRect(_poiMousePos, stackBoundingBox))
	{
		m_pStackGrabbed = _staStack->SplitStack(_staStack->ClickedCardIndex(_poiMousePos));

		if (m_pStackGrabbed != nullptr)
		{
			m_pStackGrabbedFromStack = _staStack;
			return true;
		}
	}
	
	return false;


	/*test->SetPos({ stackRect.left + _poiMousePos.x - s_poiPreviousMousePos.x,
		stackRect.top + _poiMousePos.y - s_poiPreviousMousePos.y });*/

	/*_staStack->SetPos({ stackRect.left + _poiMousePos.x - s_poiPreviousMousePos.x,
		stackRect.top + _poiMousePos.y - s_poiPreviousMousePos.y });*/
}

void CGame::MoveGrabbedStack(POINT _poiMousePos)
{
	m_pStackGrabbed->SetPos({ m_pStackGrabbed->GetPos().x + _poiMousePos.x - s_poiPreviousMousePos.x,
	                          m_pStackGrabbed->GetPos().y + _poiMousePos.y - s_poiPreviousMousePos.y });
}

void CGame::PlaceGrabbedStack(POINT _poiMousePos)
{
	std::vector<ABStack *> vecpColidedStack = ColidingStack(m_pStackGrabbed);
	bool bStackPlaced = false;

	for (ABStack* pStack : vecpColidedStack)
	{
		// Trying placing the stack
		bStackPlaced = pStack->TryPlace(m_pStackGrabbed);

		if (bStackPlaced == true)
		{
			// Notify old stack of change
			m_pStackGrabbedFromStack->NotifyChange();

			pStack->SetPos(pStack->GetPos());
			break;
		}
	}
	if (bStackPlaced == false)
	{
		// Return m_pStackGrabbed to its old stack
		m_pStackGrabbedFromStack->Place(m_pStackGrabbed);
		m_pStackGrabbedFromStack->SetPos(m_pStackGrabbedFromStack->GetPos());
	}

	delete m_pStackGrabbed;
	m_pStackGrabbed = nullptr;
	m_pStackGrabbedFromStack = nullptr;
}

void CGame::HandleClick()
{
	// Put cards from stock into waste when the player clicks the stock
	if (InsideRect(s_poiMousePos, m_pStockStack->GetBoundingBox()))
	{
		if (m_pStockStack->Empty())
		{
			// Reset stock and clear waste
			while(!m_pWasteStack->Empty())
			{
				CCard* pCard = m_pWasteStack->Top();
				m_pWasteStack->Pop();
				m_pStockStack->Push(pCard);
				pCard->HideCard();
			}
		}
		else
		{
			// Add 3 cards from the stock to the waste
			for (size_t i = 0; i < CWasteStack::s_kszNumWasteRevealed && !m_pStockStack->Empty(); ++i)
			{
				CCard* pCard = m_pStockStack->Top();
				m_pStockStack->Pop();
				m_pWasteStack->Push(pCard);
				pCard->RevealCard();
			}
		}

		m_bClickToHandle = false;
		return;
	}

	// Handle clicking on grabable cards
	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		if (!m_arrpTableauStacks.at(i)->Empty())
		{
			if(SelectStack(m_arrpTableauStacks.at(i), s_poiMousePos))
			{
				m_bClickToHandle = false;
				return;
			}
		}
	}
	for (int i = 0; i < s_kszNumFoundationStacks; ++i)
	{
		if (!m_arrpFoundationStacks.at(i)->Empty())
		{
			if (SelectStack(m_arrpFoundationStacks.at(i), s_poiMousePos))
			{
				m_bClickToHandle = false;
				return;
			}
		}
	}
	if (!m_pWasteStack->Empty())
	{
		SelectStack(m_pWasteStack, s_poiMousePos);
	}

	m_bClickToHandle = false;
	return;
}

void CGame::HandleClickRelease()
{
	if (m_pStackGrabbed != nullptr)
	{
		PlaceGrabbedStack(s_poiMousePos);
	}
	m_bClickReleaseToHandle = false;
}

std::vector<ABStack *> CGame::ColidingStack(ABStack * pStack)
{
	std::vector<ABStack *> vecpCollidingStacks;
	RECT otherStackRect;
	RECT stackRect = pStack->GetBoundingBox();
	for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		otherStackRect = m_arrpTableauStacks.at(i)->GetBoundingBox();

		if (stackRect.left < otherStackRect.right && stackRect.right > otherStackRect.left &&
			stackRect.top < otherStackRect.bottom && stackRect.bottom > otherStackRect.top)
		{
			vecpCollidingStacks.push_back(m_arrpTableauStacks.at(i));
		}
	}
	for (int i = 0; i < s_kszNumFoundationStacks; ++i)
	{
		otherStackRect = m_arrpFoundationStacks.at(i)->GetBoundingBox();

		if (stackRect.left < otherStackRect.right && stackRect.right > otherStackRect.left &&
			stackRect.top < otherStackRect.bottom && stackRect.bottom > otherStackRect.top)
		{
			vecpCollidingStacks.push_back(m_arrpFoundationStacks.at(i));
		}
	}
	return vecpCollidingStacks;
}

void
CGame::ExecuteOneFrame()
{
    float fDT = m_pClock->GetDeltaTick();

	//TODO: Remove this temp if statment setting the top card to be revealed
	/*for (int i = 0; i < s_kszNumTableauStacks; ++i)
	{
		if (m_arrpTableauStacks.at(i)->Top()->GetIsRevealed() == false)
		{
			m_arrpTableauStacks.at(i)->Top()->RevealCard();
		}
	}*/

    Process(fDT);
    Draw();

    m_pClock->Process();
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
