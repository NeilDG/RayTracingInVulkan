#include "InspectorScreen.h"
#include "imgui.h"
// #include "GameObjectManager.h"
#include "UIManager.h"
// #include "AHittable.h"

InspectorScreen::InspectorScreen() : AUIScreen("InspectorScreen")
{
}

InspectorScreen::~InspectorScreen()
{
	
}

void InspectorScreen::drawUI()
{
	
	ImGui::Begin("Inspector Window", 0, ImGuiWindowFlags_NoResize);
	// this->selectedObject = GameObjectManager::getInstance()->getSelectedObject();
	// if (this->selectedObject != nullptr) {
	// 	String name =  this->selectedObject->getName();
	// 	ImGui::Text("Selected Object: %s", name.c_str());
	// 	this->updateTransformDisplays();
	// 	bool enabled = this->selectedObject->isEnabled();
	// 	if (ImGui::Checkbox("Enabled", &enabled)) { this->selectedObject->setEnabled(enabled); }
	// 	ImGui::SameLine();
	// 	if (ImGui::Button("Delete")) { 
	// 		GameObjectManager::getInstance()->deleteObject(this->selectedObject);
	// 		GameObjectManager::getInstance()->setSelectedObject(static_cast<std::shared_ptr<AHittable>>(nullptr));
	// 	}
	// 	if (ImGui::InputFloat3("Position", this->positionDisplay)) { this->onTransformUpdate(); }
	// 	if (ImGui::InputFloat3("Rotation", this->rotationDisplay)) { this->onTransformUpdate(); }
	//
	// 	if(this->selectedObject->getType() == AHittable::SPHERE)
	// 	{
	// 		if (ImGui::InputFloat("Radius", this->scaleDisplay)) { this->onTransformUpdate(); }
	// 	}
	// 	else {
	// 		if (ImGui::InputFloat3("Scale", this->scaleDisplay)) { this->onTransformUpdate(); }
	// 	}
	//
	// 	this->drawMaterialsTab();
	// }
	// else {
	// 	ImGui::Text("No object selected. Select an object first.");
	// }
	ImGui::Text("No object selected. Select an object first.");
	ImGui::End();
}

void InspectorScreen::updateTransformDisplays()
{
	
	// Vector3D pos = this->selectedObject->getTransform();
	// this->positionDisplay[0] = pos.getX();
	// this->positionDisplay[1] = pos.getY();
	// this->positionDisplay[2] = pos.getZ();
	//
	// Vector3D rot = this->selectedObject->getRotAngles();
	// this->rotationDisplay[0] = rot.getX();
	// this->rotationDisplay[1] = rot.getY();
	// this->rotationDisplay[2] = rot.getZ();
	//
	// Vector3D scale = this->selectedObject->getScale();
	// this->scaleDisplay[0] = scale.getX();
	// this->scaleDisplay[1] = scale.getY();
	// this->scaleDisplay[2] = scale.getZ();
}

void InspectorScreen::SendResult(String materialPath)
{
	// TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObject);
	// texturedObj->getRenderer()->setMaterialPath(materialPath);
	// this->popupOpen = false;
}

void InspectorScreen::FormatMatImage()
{
	//convert to wchar format
	// String textureString = this->materialPath;
	// std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
	// const wchar_t* texturePath = widestr.c_str();
	//
	// this->materialDisplay = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
}

void InspectorScreen::drawMaterialsTab()
{
	int BUTTON_WIDTH = 225;
	int BUTTON_HEIGHT = 20;

	// if(this->selectedObject->getType() != AHittable::TEXTURED_CUBE)
	// {
	// 	return;
	// }
	
	// TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObject);
	// this->materialPath = texturedObj->getRenderer()->getMaterialPath();
	// this->FormatMatImage();
	// ImGui::SetCursorPosX(50);
	// ImGui::Image(static_cast<void*>(this->materialDisplay->getShaderResource()), ImVec2(150, 150));
	//
	// std::vector<String> paths = StringUtils::split(this->materialPath, '\\');
	// this->materialName = paths[paths.size() - 1];
	// String displayText = "Material: " + this->materialName;
	// ImGui::Text(displayText.c_str());
	// if (ImGui::Button("Add Material", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
	// 	this->popupOpen = !this->popupOpen;
	// 	UINames uiNames;
	// 	MaterialScreen* materialScreen = static_cast<MaterialScreen*>(UIManager::getInstance()->findUIByName(uiNames.MATERIAL_SCREEN));
	// 	materialScreen->linkInspectorScreen(this, this->materialPath);
	// 	UIManager::getInstance()->setEnabled(uiNames.MATERIAL_SCREEN, this->popupOpen);
	// }
}

void InspectorScreen::onTransformUpdate() const
{
	// if (this->selectedObject != nullptr) {
	// 	// ActionHistory::getInstance()->recordAction(this->selectedObject);
	//
	// 	this->selectedObject->setPosition(this->positionDisplay[0], this->positionDisplay[1], this->positionDisplay[2]);
	// 	this->selectedObject->setRotAngles(this->rotationDisplay[0], this->rotationDisplay[1], this->rotationDisplay[2]);
	//
	// 	if(this->selectedObject->getType() == AHittable::SPHERE)
	// 	{
	// 		this->selectedObject->setScale(this->scaleDisplay[0], this->scaleDisplay[0], this->scaleDisplay[0]);
	// 	}
	// 	else
	// 	{
	// 		this->selectedObject->setScale(this->scaleDisplay[0], this->scaleDisplay[1], this->scaleDisplay[2]);
	// 	}
	// 	
	// }
}
