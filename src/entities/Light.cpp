#include "Light.h"

Light::Light(glm::vec3 positions, glm::vec3 colour)
{
	this->positions = positions;
	this->colour = colour;
}

glm::vec3 Light::getPositions()
{
	return this->positions;
}

void Light::setPositsions(glm::vec3 positions)
{
	this->positions = positions;
}

glm::vec3 Light::getColour()
{
	return this->colour;
}

void Light::setColour(glm::vec3 colour)
{
	this->colour = colour;
}
