#include "Entity.h"

Entity::Entity(WorldApi *worldApi, glm::vec3 position, glm::vec3 rotation)
{
	this->position = position;
	this->rotation = rotation;
	this->worldApi = worldApi;
}

glm::vec3 Entity::getPosition()
{
	return this->position;
}

void Entity::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Entity::getRotation()
{
	return this->rotation;
}

void Entity::setRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}
void Entity::increasePosition(float dx, float dy, float dz)
{
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz)
{
	this->rotation.x += dx;
	this->rotation.y += dy;
	this->rotation.z += dz;
}

glm::vec3* Entity::getPositionPTR()
{
	return &this->position;
}