#pragma once
#include "../renderEngine/DisplayManager.h"
#include "Entity.h"
#include "../core/cbase_world.h"
#include <glm.hpp>

class Camera: public Entity
{
private:
	glm::vec3 cameraOffset= glm::vec3(0, 10, 0);
public:
	Camera(World *worldContext);
	void move(glm::vec3 positions);
};

