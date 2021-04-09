#pragma once
#include <glm.hpp>
#include "../entities/Camera.h"
class Maths
{
public:
	static glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale);
	static glm::mat4 createViewMatrix(Camera* camera);
};

