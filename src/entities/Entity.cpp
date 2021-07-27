#include "Entity.h"

Entity::Entity(glm::vec3 position, glm::vec3 rotation)
{
	this->position = position;
	this->rotation = rotation;
}

/*void Entity::setWorldContext(World *worldContext)
{
	this->worldContext->worldEvents->SubscribeEvent("onCreate", std::bind(&Entity::onBegin, this));
	this->worldContext->worldEvents->SubscribeEvent("onTick", std::bind(&Entity::onTick, this));
	this->worldContext->worldEvents->SubscribeEvent("onQuit", std::bind(&Entity::onQuit, this));
}*/

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