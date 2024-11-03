#pragma once
#include "UserSettings.hpp"
#include "From-GDGRAP2/AUIScreen.h"

class UIManager;
class LightingSettingsScreen :    public AUIScreen
{
public:
	LightingSettingsScreen();
	~LightingSettingsScreen() = default;

	void assignSettingsRef(UserSettings* settings);

private:
	UserSettings* settings;
	virtual void drawUI() override;
	friend class UIManager;
};

