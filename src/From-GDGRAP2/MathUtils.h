#pragma once
#include <cmath>
#include <limits>
#include <memory>
#include <glm/vec3.hpp>

class MathUtils
{
public:
	static float infinity();
	static float degreesToRadians(float degrees);
	static float randomFloat();
	static float randomFloat(float min, float max);

	typedef glm::vec3 Vector3D;
	static Vector3D randomFloatVec3();
	static Vector3D randomFloatVec3(float min, float max);
	
	static int randomInt(int min, int max, bool exclusive = false);
};

