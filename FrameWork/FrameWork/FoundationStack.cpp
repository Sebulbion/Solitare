#include "FoundationStack.h"



CFoundationStack::CFoundationStack() :
	IStack()
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

int CFoundationStack::ClickedCardIndex(POINT _poiMousePos)
{
	return 0;
}

void CFoundationStack::NotifyChange()
{
}
