#pragma once
#include "AUIScreen.h"
#include "GameObject.h"

class PictureSettingsScreen :    public AUIScreen
{

public:
	PictureSettingsScreen();
	~PictureSettingsScreen();
	
private:
	virtual void drawUI() override;
	friend class UIManager;
	
	
};

