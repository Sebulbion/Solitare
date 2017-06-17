#include "FoundationStack.h"



CFoundationStack::CFoundationStack()
{
}


CFoundationStack::~CFoundationStack()
{
}

bool CFoundationStack::TryPlace(IStack * pStack)
{
	return false;
}

IStack * CFoundationStack::SplitStack(int _iIndex)
{
	return nullptr;
}

void CFoundationStack::Draw()
{
}

RECT CFoundationStack::GetClickableArea()
{
	return RECT();
}

int CFoundationStack::ClickedCardIndex(POINT _poiMousePos)
{
	return 0;
}

void CFoundationStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
}
