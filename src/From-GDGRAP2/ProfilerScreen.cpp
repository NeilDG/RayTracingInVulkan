#include "ProfilerScreen.h"
#include "imgui.h"

ProfilerScreen::ProfilerScreen():AUIScreen("ProfilerScreen")
{

}

ProfilerScreen::~ProfilerScreen()
{
	AUIScreen::~AUIScreen();
}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Profiler");
	ImGui::Text("Frame rate: %.1f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}
