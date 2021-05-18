#pragma once
#include "../renderEngine/DisplayManager.h"
#include <glm.hpp>
class Camera
{
private:
	glm::vec3 positions;
	glm::vec3 rotation = glm::vec3(0, 0, 0);

	glm::vec3 cameraOffset= glm::vec3(0, 30, 0);
public:
	Camera();
	void move(glm::vec3 positions);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
};

