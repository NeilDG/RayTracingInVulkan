#include "SceneList.hpp"
#include "Assets/Material.hpp"
#include "Assets/Model.hpp"
#include "Assets/Texture.hpp"
#include <functional>
#include <random>

#include "From-GDGRAP2/GameObject.h"
#include "From-GDGRAP2/MathUtils.h"
#include "From-GDGRAP2/ModelManager.h"
#include "From-GDGRAP2/VectorUtils.h"

using namespace glm;
using Assets::Material;
using Assets::Model;
using Assets::Texture;

namespace
{

	void AddRayTracingInOneWeekendCommonScene(std::vector<Assets::Model>& models, const bool& isProc, std::function<float ()>& random)
	{
		// Common models from the final scene from Ray Tracing In One Weekend book. Only the three central spheres are missing.
		// Calls to random() are always explicit and non-inlined to avoid C++ undefined evaluation order of function arguments,
		// this guarantees consistent and reproducible behaviour across different platforms and compilers.

		models.push_back(Model::CreateSphere(vec3(0, -1000, 0), 1000, Material::Lambertian(vec3(0.5f, 0.5f, 0.5f)), isProc));

		for (int i = -11; i < 11; ++i)
		{
			for (int j = -11; j < 11; ++j)
			{
				const float chooseMat = random();
				const float center_y = static_cast<float>(j) + 0.9f * random();
				const float center_x = static_cast<float>(i) + 0.9f * random();
				const vec3 center(center_x, 0.2f, center_y);

				if (length(center - vec3(4, 0.2f, 0)) > 0.9f)
				{
					if (chooseMat < 0.8f) // Diffuse
					{
						const float b = random() * random();
						const float g = random() * random();
						const float r = random() * random();

						models.push_back(Model::CreateSphere(center, 0.2f, Material::Lambertian(vec3(r, g, b)), isProc));
					}
					else if (chooseMat < 0.95f) // Metal
					{
						const float fuzziness = 0.5f * random();
						const float b = 0.5f * (1 + random());
						const float g = 0.5f * (1 + random());
						const float r = 0.5f * (1 + random());

						models.push_back(Model::CreateSphere(center, 0.2f, Material::Metallic(vec3(r, g, b), fuzziness), isProc));
					}
					else // Glass
					{
						models.push_back(Model::CreateSphere(center, 0.2f, Material::Dielectric(1.5f), isProc));
					}
				}
			}
		}
	}

}

const std::vector<std::pair<std::string, std::function<SceneAssets (SceneList::CameraInitialState&)>>> SceneList::AllScenes =
{
	{"Cube And Spheres", CubeAndSpheres},
	{"Ray Tracing In One Weekend", RayTracingInOneWeekend},
	{"Planets In One Weekend", PlanetsInOneWeekend},
	{"Lucy In One Weekend", LucyInOneWeekend},
	{"Cornell Box", CornellBox},
	{"Cornell Box & Lucy", CornellBoxLucy},
	{"GDGRAP2 - Sphere World", GDGRAP2_SphereWorld},
	{"GRGRAP2 - Cornell Box", GDGRAP2_CornellBox}
};

SceneAssets SceneList::CubeAndSpheres(CameraInitialState& camera)
{
	// Basic test scene.
	
	camera.ModelView = translate(mat4(1), vec3(0, 0, -2));
	camera.FieldOfView = 90;
	camera.Aperture = 0.05f;
	camera.FocusDistance = 2.0f;
	camera.ControlSpeed = 2.0f;
	camera.GammaCorrection = false;
	camera.HasSky = true;

	std::vector<Model> models;
	std::vector<Texture> textures;

	models.push_back(Model::LoadModel("../assets/models/cube_multi.obj"));
	models.push_back(Model::CreateSphere(vec3(1, 0, 0), 0.5, Material::Metallic(vec3(0.7f, 0.5f, 0.8f), 0.2f), true));
	models.push_back(Model::CreateSphere(vec3(-1, 0, 0), 0.5, Material::Dielectric(1.5f), true));
	models.push_back(Model::CreateSphere(vec3(0, 1, 0), 0.5, Material::Lambertian(vec3(1.0f), 0), true));

	textures.push_back(Texture::LoadTexture("../assets/textures/land_ocean_ice_cloud_2048.png", Vulkan::SamplerConfig()));

	return std::forward_as_tuple(std::move(models), std::move(textures));
}

SceneAssets SceneList::RayTracingInOneWeekend(CameraInitialState& camera)
{
	// Final scene from Ray Tracing In One Weekend book.
	
	camera.ModelView = lookAt(vec3(13, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	camera.FieldOfView = 20;
	camera.Aperture = 0.1f;
	camera.FocusDistance = 10.0f;
	camera.ControlSpeed = 5.0f;
	camera.GammaCorrection = true;
	camera.HasSky = true;

	const bool isProc = true;

	std::mt19937 engine(42);
	std::function<float ()> random = std::bind(std::uniform_real_distribution<float>(), engine);

	std::vector<Model> models;

	AddRayTracingInOneWeekendCommonScene(models, isProc, random);

	models.push_back(Model::CreateSphere(vec3(0, 1, 0), 1.0f, Material::Dielectric(1.5f), isProc));
	models.push_back(Model::CreateSphere(vec3(-4, 1, 0), 1.0f, Material::Lambertian(vec3(0.4f, 0.2f, 0.1f)), isProc));
	models.push_back(Model::CreateSphere(vec3(4, 1, 0), 1.0f, Material::Metallic(vec3(0.7f, 0.6f, 0.5f), 0.0f), isProc));

	return std::forward_as_tuple(std::move(models), std::vector<Texture>());
}

SceneAssets SceneList::PlanetsInOneWeekend(CameraInitialState& camera)
{
	// Same as RayTracingInOneWeekend but using textures.
	
	camera.ModelView = lookAt(vec3(13, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	camera.FieldOfView = 20;
	camera.Aperture = 0.1f;
	camera.FocusDistance = 10.0f;
	camera.ControlSpeed = 5.0f;
	camera.GammaCorrection = true;
	camera.HasSky = true;

	const bool isProc = true;

	std::mt19937 engine(42);
	std::function<float()> random = std::bind(std::uniform_real_distribution<float>(), engine);

	std::vector<Model> models;
	std::vector<Texture> textures;

	AddRayTracingInOneWeekendCommonScene(models, isProc, random);

	models.push_back(Model::CreateSphere(vec3(0, 1, 0), 1.0f, Material::Metallic(vec3(1.0f), 0.1f, 2), isProc));
	models.push_back(Model::CreateSphere(vec3(-4, 1, 0), 1.0f, Material::Lambertian(vec3(1.0f), 0), isProc));
	models.push_back(Model::CreateSphere(vec3(4, 1, 0), 1.0f, Material::Metallic(vec3(1.0f), 0.0f, 1), isProc));

	textures.push_back(Texture::LoadTexture("../assets/textures/2k_mars.jpg", Vulkan::SamplerConfig()));
	textures.push_back(Texture::LoadTexture("../assets/textures/2k_moon.jpg", Vulkan::SamplerConfig()));
	textures.push_back(Texture::LoadTexture("../assets/textures/land_ocean_ice_cloud_2048.png", Vulkan::SamplerConfig()));

	return std::forward_as_tuple(std::move(models), std::move(textures));
}

SceneAssets SceneList::LucyInOneWeekend(CameraInitialState& camera)
{
	// Same as RayTracingInOneWeekend but using the Lucy 3D model.
	
	camera.ModelView = lookAt(vec3(13, 2, 3), vec3(0, 1.0, 0), vec3(0, 1, 0));
	camera.FieldOfView = 20;
	camera.Aperture = 0.05f;
	camera.FocusDistance = 10.0f;
	camera.ControlSpeed = 5.0f;
	camera.GammaCorrection = true;
	camera.HasSky = true;

	const bool isProc = true;

	std::mt19937 engine(42);
	std::function<float()> random = std::bind(std::uniform_real_distribution<float>(), engine);

	std::vector<Model> models;
	
	AddRayTracingInOneWeekendCommonScene(models, isProc, random);

	auto lucy0 = Model::LoadModel("../assets/models/lucy.obj");
	auto lucy1 = lucy0;
	auto lucy2 = lucy0;

	const auto i = mat4(1);
	const float scaleFactor = 0.0035f;

	lucy0.Transform(
		rotate(
			scale(
				translate(i, vec3(0, -0.08f, 0)), 
				vec3(scaleFactor)),
			radians(90.0f), vec3(0, 1, 0)));

	lucy1.Transform(
		rotate(
			scale(
				translate(i, vec3(-4, -0.08f, 0)),
				vec3(scaleFactor)),
			radians(90.0f), vec3(0, 1, 0)));

	lucy2.Transform(
		rotate(
			scale(
				translate(i, vec3(4, -0.08f, 0)),
				vec3(scaleFactor)),
			radians(90.0f), vec3(0, 1, 0)));

	lucy0.SetMaterial(Material::Dielectric(1.5f));
	lucy1.SetMaterial(Material::Lambertian(vec3(0.4f, 0.2f, 0.1f)));
	lucy2.SetMaterial(Material::Metallic(vec3(0.7f, 0.6f, 0.5f), 0.05f));

	models.push_back(std::move(lucy0));
	models.push_back(std::move(lucy1));
	models.push_back(std::move(lucy2));

	return std::forward_as_tuple(std::move(models), std::vector<Texture>());
}

SceneAssets SceneList::CornellBox(CameraInitialState& camera)
{
	camera.ModelView = lookAt(vec3(278, 278, 800), vec3(278, 278, 0), vec3(0, 1, 0));
	camera.FieldOfView = 40;
	camera.Aperture = 0.0f;
	camera.FocusDistance = 10.0f;
	camera.ControlSpeed = 500.0f;
	camera.GammaCorrection = true;
	camera.HasSky = false;

	const auto i = mat4(1);
	const auto white = Material::Lambertian(vec3(0.73f, 0.73f, 0.73f));

	auto box0 = Model::CreateBox(vec3(0, 0, -165), vec3(165, 165, 0), white);
	auto box1 = Model::CreateBox(vec3(0, 0, -165), vec3(165, 330, 0), white);

	box0.Transform(rotate(translate(i, vec3(555 - 130 - 165, 0, -65)), radians(-18.0f), vec3(0, 1, 0)));
	box1.Transform(rotate(translate(i, vec3(555 - 265 - 165, 0, -295)), radians(15.0f), vec3(0, 1, 0)));

	std::vector<Model> models;
	models.push_back(Model::CreateCornellBox(555));
	models.push_back(box0);
	models.push_back(box1);

	return std::make_tuple(std::move(models), std::vector<Texture>());
}

SceneAssets SceneList::CornellBoxLucy(CameraInitialState& camera)
{
	camera.ModelView = lookAt(vec3(278, 278, 800), vec3(278, 278, 0), vec3(0, 1, 0));
	camera.FieldOfView = 40;
	camera.Aperture = 0.0f;
	camera.FocusDistance = 10.0f;
	camera.ControlSpeed = 500.0f;
	camera.GammaCorrection = true;
	camera.HasSky = false;

	const auto i = mat4(1);
	const auto sphere = Model::CreateSphere(vec3(555 - 130, 165.0f, -165.0f / 2 - 65), 80.0f, Material::Dielectric(1.5f), true);
	auto lucy0 = Model::LoadModel("../assets/models/lucy.obj");

	lucy0.Transform(
		rotate(
			scale(
				translate(i, vec3(555 - 300 - 165/2, -9, -295 - 165/2)),
				vec3(0.6f)),
			radians(75.0f), vec3(0, 1, 0)));

	std::vector<Model> models;
	models.push_back(Model::CreateCornellBox(555));
	models.push_back(sphere);
	models.push_back(lucy0);

	return std::forward_as_tuple(std::move(models), std::vector<Texture>());
}

/**
 * \brief Replication of the sphere world from GDGRAP2.
 * \param camera 
 * \return 
 */
SceneAssets SceneList::GDGRAP2_SphereWorld(CameraInitialState& camera)
{
	camera.ModelView = lookAt(vec3(13, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0));
	camera.FieldOfView = 20;
	camera.Aperture = 0.01f;
	camera.FocusDistance = 10.0f;
	camera.ControlSpeed = 5.0f;
	camera.GammaCorrection = true;
	camera.HasSky = true;

	std::mt19937 engine(1);
	std::function<float()> random = std::bind(std::uniform_real_distribution<float>(), engine);

	bool isProcedural = false;
	// std::vector<Model> models;

	vec3 pos = vec3(0, -1000, 0); float center = 1000;
	Model sphere1Model = Model::CreateSphere(pos, center, Material::Lambertian(vec3(0.5f, 0.5f, 0.5f)), isProcedural);
	std::shared_ptr<GameObject> sphere1 = std::make_shared<GameObject>("GroundSphere", GameObject::PrimitiveType::SPHERE, std::make_shared<Model>(sphere1Model));
	ModelManager::getInstance()->addObject(sphere1);

	pos = vec3(0, 1, 0); center = 1.0f;
	Model sphere2Model = Model::CreateSphere(pos, 1.0f, Material::Dielectric(1.5f), isProcedural);
	std::shared_ptr<GameObject> sphere2 = std::make_shared<GameObject>("CenterSphere", GameObject::PrimitiveType::SPHERE, std::make_shared<Model>(sphere2Model));
	ModelManager::getInstance()->addObject(sphere2);

	pos = vec3(-8, 2.5f, 1); center = 2.5f;
	Model sphere3Model = Model::CreateSphere(pos, 2.5f, Material::Metallic(vec3(0.4f, 0.2f, 0.1f), MathUtils::randomFloat(0.0f, 0.2f)), isProcedural);
	std::shared_ptr<GameObject> sphere3 = std::make_shared<GameObject>("LeftSphere", GameObject::PrimitiveType::SPHERE, std::make_shared<Model>(sphere3Model));
	ModelManager::getInstance()->addObject(sphere3);

	pos = vec3(4, 1, 0); center = 1.0f;
	Model sphere4Model = Model::CreateSphere(pos, 1.0f, Material::Metallic(vec3(0.7f, 0.6f, 0.5f), 0.0f), isProcedural);
	std::shared_ptr<GameObject> sphere4 = std::make_shared<GameObject>("RightSphere", GameObject::PrimitiveType::SPHERE, std::make_shared<Model>(sphere4Model));
	ModelManager::getInstance()->addObject(sphere4);

	for(int repeats = 0; repeats < 2; repeats++)
	{
		for (int a = -11; a < 11; a++)
		{
			for (int b = -11; b < 11; b++)
			{
				float matVal = MathUtils::randomFloat();
				vec3 center(a + 0.9f * MathUtils::randomFloat(), 0.2 + (2 * MathUtils::randomFloat()), b + 0.9 * MathUtils::randomFloat());
				if ((center - vec3(4.0, 0.2f, 0.0f)).length() > 0.9f)
				{
					Material materialInstance;
	
					if (matVal < 0.8)
					{
						vec3 albedo = 2.0f * VectorUtils::randomFloatVec3();
						float fuzziness = MathUtils::randomFloat(0.0f, 0.95f);
						materialInstance = Material::Metallic(albedo, fuzziness, MathUtils::randomInt(0, 3));
					}
					else if(matVal < 0.95)
					{
						materialInstance = Material::Dielectric(MathUtils::randomFloat(0.5f, 2.5f));
					}
					else
					{
						vec3 albedo = VectorUtils::randomFloatVec3();
						materialInstance = Material::DiffuseLight(albedo);
					}
	
					Model modelInstance = Model::CreateSphere(center, MathUtils::randomFloat(0.2f, 0.4f), materialInstance, isProcedural);
					std::shared_ptr<GameObject> objectInstance = std::make_shared<GameObject>("SmallSphere", GameObject::PrimitiveType::SPHERE, std::make_shared<Model>(modelInstance));
					ModelManager::getInstance()->addObject(objectInstance);
				}
			}
		}
	
		for (int a = -5; a < 5; a++)
		{
			for (int b = -5; b < 5; b++)
			{
				vec3 center(a + 0.9f * MathUtils::randomFloat(), 0.2 + (5 * MathUtils::randomFloat()), b + 0.9 * MathUtils::randomFloat());
	
				//add additional reflective spheres
				Material materialInstance = Material::Dielectric(1.5f);
				Model modelInstance = Model::CreateSphere(center, MathUtils::randomFloat(0.1f, 0.2f), materialInstance, isProcedural);
				std::shared_ptr<GameObject> objectInstance = std::make_shared<GameObject>("SmallSphere", GameObject::PrimitiveType::SPHERE, std::make_shared<Model>(modelInstance));
				ModelManager::getInstance()->addObject(objectInstance);
			}
		}
	}

	std::vector<Model> models = ModelManager::getInstance()->getAllObjectModels();

	std::vector<Texture> textures = AssembleTextureList();
	return std::forward_as_tuple(std::move(models), std::move(textures));
}

SceneAssets SceneList::GDGRAP2_CornellBox(CameraInitialState& camera)
{
	camera.ModelView = lookAt(vec3(278, 278, 800), vec3(278, 278, 0), vec3(0, 1, 0));
	camera.FieldOfView = 40;
	camera.Aperture = 0.0f;
	camera.FocusDistance = 10.0f;
	camera.ControlSpeed = 500.0f;
	camera.GammaCorrection = true;
	camera.HasSky = false;

	std::mt19937 engine(1);
	std::function<float()> random = std::bind(std::uniform_real_distribution<float>(), engine);

	bool isProcedural = false;

	const auto i = mat4(1);
	const auto white = Material::Lambertian(vec3(0.73f, 0.73f, 0.73f));

	Model box0 = Model::CreateBox(vec3(0, 0, -165), vec3(165, 165, 0), white);
	Model box1 = Model::CreateBox(vec3(0, 0, -165), vec3(165, 330, 0), white);

	box0.Transform(rotate(translate(i, vec3(555 - 130 - 165, 0, -65)), radians(-18.0f), vec3(0, 1, 0)));
	box1.Transform(rotate(translate(i, vec3(555 - 265 - 165, 0, -295)), radians(15.0f), vec3(0, 1, 0)));

	std::shared_ptr<GameObject> box0_Object = std::make_shared<GameObject>("Box", GameObject::PrimitiveType::CUBE, std::make_shared<Model>(box0));
	ModelManager::getInstance()->addObject(box0_Object);

	std::shared_ptr<GameObject> box1_Object = std::make_shared<GameObject>("Box", GameObject::PrimitiveType::CUBE, std::make_shared<Model>(box1));
	ModelManager::getInstance()->addObject(box1_Object);

	Model cornellBoxModel = Model::CreateCornellBox(555);
	std::shared_ptr<GameObject> cornellBoxObject = std::make_shared<GameObject>("CornellBox", GameObject::PrimitiveType::CUBE, std::make_shared<Model>(cornellBoxModel));
	ModelManager::getInstance()->addObject(cornellBoxObject);

	std::vector<Model> models = ModelManager::getInstance()->getAllObjectModels();

	std::vector<Texture> textures = AssembleTextureList();
	return std::forward_as_tuple(std::move(models), std::move(textures));
}

std::vector<Assets::Texture> SceneList::AssembleTextureList()
{
	std::vector<Texture> textures;
	textures.push_back(Texture::LoadTexture("../assets/textures/2k_mars.jpg", Vulkan::SamplerConfig()));
	textures.push_back(Texture::LoadTexture("../assets/textures/2k_moon.jpg", Vulkan::SamplerConfig()));
	textures.push_back(Texture::LoadTexture("../assets/textures/land_ocean_ice_cloud_2048.png", Vulkan::SamplerConfig()));

	return textures;
}
