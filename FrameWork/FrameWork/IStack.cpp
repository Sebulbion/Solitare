#include "Stack.h"



IStack::IStack()
{
}


IStack::~IStack()
{
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

void IStack::Push(const CCard & _krCard)
{
	m_listCards.push_front(_krCard);
}

CCard & IStack::Top()
{
	return m_listCards.front();
}

void IStack::Pop()
{
	m_listCards.pop_front();
}
