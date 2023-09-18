#pragma once
#include <opencv2/core/cvstd.hpp>
/**
 * \brief Refers to the active ray-tracing rules being used. Production/debug.
 */
class RTRules
{
public:
	static RTRules* getInstance();
	static void initialize();
	static void destroy();

	enum RayTracingType
	{
		QUICK,
		PREVIEW,
		PRODUCTION
	};

	enum PathTracingType
	{
		SLIDING_WINDOW,
		MONTE_CARLO
	};

	enum RayTracingScene
	{
		SPHERE_WORLD,
		CORNELL_BOX
	};

	void setRayTracingType(RayTracingType type);
	void setPathTracingType(PathTracingType type);
	cv::String getSaveImagePath();
	friend class RayTracingProper;
	friend class RenderLayer;

private:
	RTRules();
	~RTRules();
	RTRules(RTRules const&) {}; // copy constructor is private
	RTRules& operator=(RTRules const&) {}; // assignment operator is private*/
	static RTRules* sharedInstance;

	int raySamplesPerPixel;
	int bounces;
	int width;
	float aspectRatio;
	int height;
	int numCores;
	int widthWindow;
	int heightWindow;
	cv::String saveImagePath;

	RayTracingType rayTracingType;
	PathTracingType pathTracingType;


};

