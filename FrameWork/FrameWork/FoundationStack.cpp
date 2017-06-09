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

IStack * CFoundationStack::SplitStack()
{
	return nullptr;
}

void CFoundationStack::Draw()
{
}

void CFoundationStack::SetPos(const TPosition & _krpos)
{
	m_pos = _krpos;
}
