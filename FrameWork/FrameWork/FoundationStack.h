#ifndef FOUNDATIONSTACK_H
#define FOUNDATIONSTACK_H

#include "Stack.h"

class CFoundationStack : public ABStack
{
public:
	CFoundationStack();
	virtual ~CFoundationStack();

	// Inherited via IStack
	virtual bool TryPlace(ABStack * pStack) override;
	virtual ABStack * SplitStack(int _iIndex) override;
	virtual int ClickedCardIndex(POINT _poiMousePos) override;
	virtual void NotifyChange() override;

private:
	CFoundationStack(const CFoundationStack& _kr) = delete;
	CFoundationStack& operator= (const CFoundationStack& _kr) = delete;
};
#endif //FOUNDATIONSTACK_H
