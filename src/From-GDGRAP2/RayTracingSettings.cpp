#include "RayTracingSettings.h"
#include <iostream>

RayTracingSettings* RayTracingSettings::sharedInstance = nullptr;
RayTracingSettings* RayTracingSettings::getInstance()
{
	return sharedInstance;
}

void RayTracingSettings::initialize()
{
	sharedInstance = new RayTracingSettings();
}

void RayTracingSettings::destroy()
{
	delete sharedInstance;
}

void RayTracingSettings::setRT(bool enableRT)
{
	this->enableRT = enableRT;
	this->shouldResetAccumulation = true;
}

void RayTracingSettings::setNumberOfSamples(int numberOfSamples)
{
	this->numberOfSamples = numberOfSamples;
	this->shouldResetAccumulation = true;
}

void RayTracingSettings::setNumberOfBounces(int numberOfBounces)
{
	this->numberOfBounces = numberOfBounces;
	this->shouldResetAccumulation = true;
}

void RayTracingSettings::setAll(bool enableRT, int numberOfSamples, int numberOfBounces)
{
	this->setRT(enableRT);
	this->setNumberOfSamples(numberOfSamples);
	this->setNumberOfBounces(numberOfBounces);
}

bool RayTracingSettings::isRTEnabled() const
{
	return this->enableRT;
}

int RayTracingSettings::getNumberOfSamples() const
{
	return this->numberOfSamples;
}

int RayTracingSettings::getNumberOfBounces() const
{
	return this->numberOfBounces;
}

bool RayTracingSettings::requiresResetAccumulation()
{
	bool flag = this->shouldResetAccumulation;
	this->shouldResetAccumulation = false;
	return flag;
}
