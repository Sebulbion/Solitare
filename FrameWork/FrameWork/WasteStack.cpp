#include "WasteStack.h"



CWasteStack::CWasteStack()
{
}


CWasteStack::~CWasteStack()
{
}

bool CWasteStack::TryPlace(IStack * pStack)
{
	return false;
}

IStack * CWasteStack::SplitStack(int _iIndex)
{
	return nullptr;
}

void CWasteStack::Draw()
{
}

RECT CWasteStack::GetClickableArea()
{
	return RECT();
}

int CWasteStack::ClickedCardIndex(POINT _poiMousePos)
{
	return 0;
}

void CWasteStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
}
