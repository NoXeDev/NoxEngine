#include "Light.h"

Light::Light(glm::vec3 positions, glm::vec3 rotation, glm::vec3 colour): Entity(positions, rotation)
{
	this->colour = colour;
}

glm::vec3 Light::getColour()
{
	return this->colour;
}

void Light::setColour(glm::vec3 colour)
{
	this->colour = colour;
}
