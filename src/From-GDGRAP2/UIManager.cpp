#include "UIManager.h"
#include "ConsoleScreen.h"
#include "RTConfig.h"
#include "MenuScreen.h"
#include "Debug.h"
#include "HierarchyScreen.h"
#include "InspectorScreen.h"
#include "ProfilerScreen.h"


UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize()
{
    sharedInstance = new UIManager();
}

void UIManager::destroy()
{
    delete sharedInstance;
}

void UIManager::drawAllUI()
{
	for (int i = 0; i < this->uiList.size(); i++) {
		this->uiList[i]->drawUI();
	}
}

void UIManager::setEnabled(String uiName, bool flag)
{
	if(this->uiTable[uiName] != nullptr)
	{
		this->uiTable[uiName]->SetEnabled(flag);
	}
}

std::shared_ptr<AUIScreen> UIManager::findUIByName(String uiName)
{
	if(this->uiTable[uiName] != nullptr)
	{
		return this->uiTable[uiName];
	}
	else
	{
		return nullptr;
	}
}

UIManager::UIManager()
{
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

    //populate UI table
	//UIs that will show during runtime
	UINames uiNames;

	std::shared_ptr<MenuScreen> menuScreen = std::make_shared<MenuScreen>();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	std::shared_ptr<HierarchyScreen> hierarchyScreen = std::make_shared<HierarchyScreen>();
	this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	this->uiList.push_back(hierarchyScreen);

	std::shared_ptr<InspectorScreen> inspectorScreen = std::make_shared<InspectorScreen>();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	std::shared_ptr<ConsoleScreen> consoleScreen = std::make_shared<ConsoleScreen>();
	this->uiTable[uiNames.CONSOLE_SCREEN] = consoleScreen;
	this->uiList.push_back(consoleScreen);
	Debug::assignConsole(consoleScreen);

	std::shared_ptr<ProfilerScreen> profilerScreen = std::make_shared<ProfilerScreen>();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);
	//
	// MaterialScreen* materialScreen = new MaterialScreen();
	// this->uiTable[uiNames.MATERIAL_SCREEN] = materialScreen;
	// this->uiList.push_back(materialScreen);
	// materialScreen->SetEnabled(false);

	Debug::Log("Initialized UIs!");
}

UIManager::~UIManager()
{
}
