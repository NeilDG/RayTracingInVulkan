#pragma once
#include "Utilities/Glm.hpp"
#include <functional>
#include <string>
#include <tuple>
#include <vector>

namespace Assets
{
	class Model;
	class Texture;
}

typedef std::tuple<std::vector<Assets::Model>, std::vector<Assets::Texture>> SceneAssets;

class SceneList final
{
public:

	struct CameraInitialState
	{
		glm::mat4 ModelView;
		float FieldOfView;
		float Aperture;
		float FocusDistance;
		float ControlSpeed;
		bool GammaCorrection;
		bool HasSky;
	};

	static SceneAssets CubeAndSpheres(CameraInitialState& camera);
	static SceneAssets RayTracingInOneWeekend(CameraInitialState& camera);
	static SceneAssets PlanetsInOneWeekend(CameraInitialState& camera);
	static SceneAssets LucyInOneWeekend(CameraInitialState& camera);
	static SceneAssets CornellBox(CameraInitialState& camera);
	static SceneAssets CornellBoxLucy(CameraInitialState& camera);

	static SceneAssets GDGRAP2_SphereWorld(CameraInitialState& camera);
	static SceneAssets GDGRAP2_CornellBox(CameraInitialState& camera);
	static SceneAssets GDGRAP2_BoxWorld(CameraInitialState& camera);
	static std::vector<Assets::Texture> AssembleTextureList();

	static const std::vector<std::pair<std::string, std::function<SceneAssets (CameraInitialState&)>>> AllScenes;
};
