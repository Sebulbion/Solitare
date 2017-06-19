#ifndef TABLEAUSTACK_H
#define TABLEAUSTACK_H

#include <Windows.h>
#include "Stack.h"

class CTableauStack : public ABStack
{
public:
	CTableauStack();
	virtual ~CTableauStack();

	// Inherited via IStack
	virtual bool TryPlace(ABStack * pStack) override;
	virtual ABStack * SplitStack(int _iIndex) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

private:
	CTableauStack(const CTableauStack& _kr) = delete;
	CTableauStack& operator= (const CTableauStack& _kr) = delete;

	int m_iCardOffset;
};
#endif //TABLEAUSTACK_H
