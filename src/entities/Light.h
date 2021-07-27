#pragma once
#include <glm.hpp>
#include "Entity.h"
class Light: public Entity
{
public:
	Light(glm::vec3 positions, glm::vec3 rotation, glm::vec3 colour);
	glm::vec3 getColour();
	void setColour(glm::vec3 colour);

private:
	glm::vec3 colour;
};