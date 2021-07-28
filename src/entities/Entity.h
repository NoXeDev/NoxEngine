#pragma once
#include "../model/TexturedModel.h"
#include "../core/worldApi.h"
#include <glm.hpp>
#include <iostream>
class Entity
{
protected:
	glm::vec3 position;
	glm::vec3 rotation;
	WorldApi *worldApi;

public:
	Entity(WorldApi *worldApi, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0));

	//getters and setters
	glm::vec3* getPositionPTR();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getRotation();
	void setRotation(glm::vec3 rotation);

	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);
};

