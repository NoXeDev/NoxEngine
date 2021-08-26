#pragma once
#include <glm.hpp>
#include "Entity.h"
class Light: public Entity
{
public:
	Light(WorldApi *worldApi, glm::vec3 positions, glm::vec3 rotation, glm::vec3 colour, glm::vec3 attenuation = glm::vec3(1, 0, 0));
	glm::vec3 getColour();
	void setColour(glm::vec3 colour);
	glm::vec3 getAttenuation();

private:
	glm::vec3 colour;
	glm::vec3 attenuation;
};