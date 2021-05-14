#pragma once
#include <glm.hpp>
#include "../renderEngine/DisplayManager.h"
class Camera
{
private:
	glm::vec3 positions;
	glm::vec3 rotation = glm::vec3(0, 0, 0);
public:
	Camera(glm::vec3 positions);
	void move();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
};

