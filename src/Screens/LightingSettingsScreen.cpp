#include "LightingSettingsScreen.h"

#include <imgui.h>

LightingSettingsScreen::LightingSettingsScreen(): AUIScreen("LightingSettingsScreen")
{
}

void LightingSettingsScreen::assignSettingsRef(UserSettings* settings)
{
	this->settings = settings;
}

void LightingSettingsScreen::drawUI()
{
	//Create a popup window with a close button.
	ImGui::Begin("Lighting Settings", &this->enabled, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(512, 512));
	ImGui::Text("Ray Tracing");
	ImGui::Separator();
	ImGui::Checkbox("Accumulate rays between frames", &this->settings->AccumulateRays);
	uint32_t min = 1, max = 128;
	ImGui::SliderScalar("Samples", ImGuiDataType_U32, &this->settings->NumberOfSamples, &min, &max);
	min = 1, max = 32;
	ImGui::SliderScalar("Bounces", ImGuiDataType_U32, &this->settings->NumberOfBounces, &min, &max);
	ImGui::NewLine();

	ImGui::End();
	
}
