#pragma once
#include <glm.hpp>
#include "../entities/Camera.h"
class Maths
{
public:
	static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
	static glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);
	static glm::mat4 createViewMatrix(Camera* camera);
};

