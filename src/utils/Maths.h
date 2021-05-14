#pragma once
#include <glm.hpp>
#include "../entities/Camera.h"
class Maths
{
public:
	static glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);
	static glm::mat4 createViewMatrix(Camera* camera);
};

