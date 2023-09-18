#pragma once
#include "AUIScreen.h"

class UIManager;
class ProfilerScreen :    public AUIScreen
{
public:
	ProfilerScreen();
	~ProfilerScreen();
private:
	virtual void drawUI() override;
	friend class UIManager;
};

