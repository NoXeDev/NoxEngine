#include "Light.h"

Light::Light(WorldApi *worldApi, glm::vec3 positions, glm::vec3 rotation, glm::vec3 colour, glm::vec3 attenuation): Entity(worldApi, positions, rotation)
{
	this->colour = colour;
	this->attenuation = attenuation;
}

glm::vec3 Light::getAttenuation()
{
	return this->attenuation;
}

glm::vec3 Light::getColour()
{
	return this->colour;
}

void Light::setColour(glm::vec3 colour)
{
	this->colour = colour;
}
