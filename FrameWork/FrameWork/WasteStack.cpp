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

IStack * CWasteStack::SplitStack()
{
	return nullptr;
}

void CWasteStack::Draw()
{
}

void CWasteStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
}
