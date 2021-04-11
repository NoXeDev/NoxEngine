#pragma once
#include <glm.hpp>
#include "../renderEngine/DisplayManager.h"
class Camera
{
private:
	glm::vec3 positions;
	float pitch = 0;
	float yaw = 0;
	float roll = 0;
	DisplayManager *display;
public:
	Camera(glm::vec3 positions);
	void move();
	glm::vec3 getPosition();
	float getPitch();
	float getYaw();
	float getRoll();
};

