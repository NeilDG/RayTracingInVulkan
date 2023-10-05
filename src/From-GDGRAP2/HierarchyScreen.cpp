#include "HierarchyScreen.h"
#include "imgui.h"
#include "From-GDGRAP2/ModelManager.h"
#include "UIManager.h"
#include "RTConfig.h"

HierarchyScreen::HierarchyScreen(): AUIScreen("HierarchyScreen")
{
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::drawUI()
{
	ImGui::Begin("Scene Outline");
	this->updateObjectList();
	ImGui::End();
}

void HierarchyScreen::updateObjectList() const
{
	const ModelManager::List objectList= ModelManager::getInstance()->getAllObjects();
	for (int i = 0; i < objectList.size(); i++) {
		String objectName = objectList[i]->getName();
		if (ImGui::Button(objectName.c_str(), ImVec2(235, 0))) {
			ModelManager::getInstance()->setSelectedObject(objectName);
		}
	}
}
