#pragma once
#include <glm.hpp>
#include "../renderEngine/DisplayManager.h"
class Camera
{
private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	float pitch = 0;
	float yaw = 0;
	float roll = 0;
	DisplayManager *display;
public:
	void move();
	glm::vec3 getPosition();
	float getPitch();
	float getYaw();
	float getRoll();
};

