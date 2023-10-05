#include "PictureSettingsScreen.h"
#include "imgui.h"
#include "ModelManager.h"
#include "UIManager.h"
#include "GameObject.h"
#include "GlobalConfig.h"
#include "RayTracingSettings.h"
#include "UserSettings.hpp"
#include "SceneCamera.h"

PictureSettingsScreen::PictureSettingsScreen(): AUIScreen("PictureSettingsScreen")
{

}

PictureSettingsScreen::~PictureSettingsScreen()
{
}

void PictureSettingsScreen::drawUI()
{
	const auto flags =
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize;

	ImGui::Begin("Picture Settings", 0, flags);

	ImGui::Text("Instructions");
	ImGui::Separator();
	ImGui::BulletText(
		"%c%c%c%c/SHIFT/CTRL: move camera.",
		std::toupper('W'),
		std::toupper('A'),
		std::toupper('S'),
		std::toupper('D'));
	ImGui::BulletText("L/R Mouse: rotate camera/scene.");
	ImGui::NewLine();

	bool enableRT = RayTracingSettings::getInstance()->isRTEnabled();
	int samples = RayTracingSettings::getInstance()->getNumberOfSamples();
	int bounces = RayTracingSettings::getInstance()->getNumberOfBounces();
	ImGui::Text("Ray Tracing");
	ImGui::Separator();
	ImGui::Checkbox("Enable ray tracing", &enableRT);
	// ImGui::Checkbox("Accumulate rays between frames", nullptr);
	uint32_t min = 1, max = 512;
	ImGui::SliderScalar("Samples", ImGuiDataType_U32, &samples, &min, &max);
	min = 1, max = 32;
	ImGui::SliderScalar("Bounces", ImGuiDataType_U32, &bounces, &min, &max);
	ImGui::NewLine();

	RayTracingSettings::getInstance()->setAll(enableRT, samples, bounces);

	float fov = SceneCamera::getInstance()->getFieldOfView();
	float aperture = SceneCamera::getInstance()->getAperture();
	float focus = SceneCamera::getInstance()->getFocusDistance();

	ImGui::Text("Camera");
	ImGui::Separator();
	ImGui::SliderFloat("FoV", &fov, UserSettings::FieldOfViewMinValue, UserSettings::FieldOfViewMaxValue, "%.0f");
	ImGui::SliderFloat("Aperture", &aperture, 0.0f, 1.0f, "%.2f");
	ImGui::SliderFloat("Focus", &focus, 0.1f, 20.0f, "%.1f");
	ImGui::NewLine();

	SceneCamera::getInstance()->setAll(fov, aperture, focus);

	ImGui::End();
}
