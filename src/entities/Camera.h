#pragma once
#include "../renderEngine/DisplayManager.h"
#include "Entity.h"
#include <glm.hpp>

class Camera: public Entity
{
private:
	glm::vec3 cameraOffset= glm::vec3(0, 10, 0);
public:
	Camera(WorldApi *worldApi);
	void move(glm::vec3 positions);

	WorldApi *getWorldApi(){
		return this->worldApi;
	}
};

