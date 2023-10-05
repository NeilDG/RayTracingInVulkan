#include "SceneCamera.h"
#include <iostream>

SceneCamera* SceneCamera::sharedInstance = nullptr;

SceneCamera* SceneCamera::getInstance()
{
	return sharedInstance;
}

void SceneCamera::initialize()
{
	sharedInstance = new SceneCamera();
}

void SceneCamera::destroy()
{
	delete sharedInstance;
}


SceneCamera::SceneCamera()
{
}

void SceneCamera::setFieldOfView(float fieldOfView)
{
	this->fieldOfView = fieldOfView;
	this->shouldResetAccumulation = true;
}

void SceneCamera::setAperture(float aperture)
{
	this->aperture = aperture;
	this->shouldResetAccumulation = true;
}

void SceneCamera::setFocusDistance(float focusDistance)
{
	this->focusDistance = focusDistance;
	this->shouldResetAccumulation = true;
}

void SceneCamera::setAll(float fieldOfView, float aperture, float focusDistance)
{
	this->setFieldOfView(fieldOfView);
	this->setAperture(aperture);
	this->setFocusDistance(focusDistance);
}

bool SceneCamera::requiresResetAccumulation()
{
	bool flag = this->shouldResetAccumulation;
	this->shouldResetAccumulation = false;
	return flag;
}

float SceneCamera::getFieldOfView() const
{
	return this->fieldOfView;
}

float SceneCamera::getAperture() const
{
	return this->aperture;
}

float SceneCamera::getFocusDistance() const
{
	return this->focusDistance;
}
