#pragma once
#include "From-GDGRAP2/SceneCamera.h"
#include "From-GDGRAP2/RayTracingSettings.h"

struct UserSettings final
{
	// Application
	bool Benchmark;

	// Benchmark
	bool BenchmarkNextScenes{};
	uint32_t BenchmarkMaxTime{};
	
	// Scene
	int SceneIndex;

	// Renderer
	// bool IsRayTraced;
	bool AccumulateRays;
	// uint32_t NumberOfSamples;
	// uint32_t NumberOfBounces;
	uint32_t MaxNumberOfSamples;

	// Camera
	// float FieldOfView;
	// float Aperture;
	// float FocusDistance;

	// Profiler
	bool ShowHeatmap;
	float HeatmapScale;

	// UI
	bool ShowSettings;
	bool ShowOverlay;

	inline const static float FieldOfViewMinValue = 10.0f;
	inline const static float FieldOfViewMaxValue = 90.0f;

	bool RequiresAccumulationReset(const UserSettings& prev) const
	{
		return
			// IsRayTraced != prev.IsRayTraced ||
			AccumulateRays != prev.AccumulateRays ||
			// NumberOfBounces != prev.NumberOfBounces ||
			RayTracingSettings::getInstance()->requiresResetAccumulation() ||
			SceneCamera::getInstance()->requiresResetAccumulation();
			// FieldOfView != prev.FieldOfView ||
			// Aperture != prev.Aperture ||
			// FocusDistance != prev.FocusDistance;
	}
};
