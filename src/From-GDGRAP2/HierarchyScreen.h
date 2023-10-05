#pragma once
#include "AUIScreen.h"
class HierarchyScreen :    public AUIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();
private:
	virtual void drawUI() override;
	void updateObjectList() const;
	friend class UIManager;
};

