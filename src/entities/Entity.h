#pragma once
#include "../model/TexturedModel.h"
//#include "../core/cbase_world.h"
#include <glm.hpp>
#include <iostream>
class Entity
{
protected:
	glm::vec3 position;
	glm::vec3 rotation;

public:
	Entity(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0));

	//getters and setters
	glm::vec3* getPositionPTR();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getRotation();
	void setRotation(glm::vec3 rotation);

	//void setWorldContext(World *worldContext);

	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);

	virtual void onBegin() = 0;
	virtual void onTick() = 0;
	virtual void onQuit() = 0;
};

