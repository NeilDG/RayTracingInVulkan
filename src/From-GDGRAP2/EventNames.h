#pragma once
#include <string>

class EventNames
{
public:
	typedef std::string String;
	inline static const String ON_RAY_TRACE_CONFIG_CHANGED = "ON_RAY_TRACE_CONFIG_CHANGED";
	inline static const String ON_RAY_TRACE_COMPUTE_FINISHED = "ON_RAY_TRACE_COMPUTE_FINISHED";
	inline static const String ON_SCENE_LOADED = "ON_SCENE_LOADED";
};

