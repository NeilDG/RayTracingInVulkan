#pragma once
#include <memory>
#include <string>
#include <glm/vec3.hpp>

#include "SceneList.hpp"

class SceneCamera final
{
public:
	static SceneCamera* getInstance();
	static void initialize();
	static void destroy();

	typedef glm::vec3 vec3;
	typedef std::string String;

	void setFieldOfView(float fieldOfView);
	void setAperture(float aperture);
	void setFocusDistance(float focusDistance);
	void setAll(float fieldOfView, float aperture, float focusDistance);
	bool requiresResetAccumulation();

	float getFieldOfView() const;
	float getAperture() const;
	float getFocusDistance() const;

private:
	SceneCamera();
	~SceneCamera() = default;
	SceneCamera(SceneCamera const&) {}; // copy constructor is private
	SceneCamera& operator=(SceneCamera const&) {}; // assignment operator is private*/
	static SceneCamera* sharedInstance;

	float fieldOfView = 0.0f;
	float aperture = 0.0f;
	float focusDistance = 0.0f;

	bool shouldResetAccumulation = false;
 };

