#pragma once
#include <memory>
#include <string>
#include <glm/vec3.hpp>

class RayTracingSettings final
{
public:
	typedef glm::vec3 vec3;
	typedef std::string String;

	static RayTracingSettings* getInstance();
	static void initialize();
	static void destroy();

	void setRT(bool enableRT);
	void setNumberOfSamples(int numberOfSamples);
	void setNumberOfBounces(int numberOfBounces);
	void setAll(bool enableRT, int numberOfSamples, int numberOfBounces);

	bool isRTEnabled() const;
	int getNumberOfSamples() const;
	int getNumberOfBounces() const;
	bool requiresResetAccumulation();

private:
	RayTracingSettings() = default;
	~RayTracingSettings() = default;
	RayTracingSettings(RayTracingSettings const&) {}; // copy constructor is private
	RayTracingSettings& operator=(RayTracingSettings const&) {}; // assignment operator is private*/
	static RayTracingSettings* sharedInstance;

	bool enableRT = true;
	int numberOfSamples = 32;
	int numberOfBounces = 4;

	bool shouldResetAccumulation = false;

 };

