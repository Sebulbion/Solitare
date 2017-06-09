#include "Stack.h"



IStack::IStack()
{
}


IStack::~IStack()
{
}

void IStack::SetPos(const TPosition& _krpos)
{
	m_pos = _krpos;
}

TPosition IStack::GetPos() const
{
	return m_pos;
}

float IStack::GetWidth() const
{
	return m_fWidth;
}

float IStack::GetHeight() const
{
	return m_fHeight;
}
