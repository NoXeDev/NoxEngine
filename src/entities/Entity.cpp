#include "Entity.h"

Entity::Entity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, float scale)
{
	this->model = model;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

TexturedModel* Entity::getModel()
{
	return this->model;
}

void Entity::setModel(TexturedModel* model)
{
	this->model = model;
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

float Entity::getScale()
{
	return this->scale;
}

void Entity::setScale(float scale)
{
	this->scale = scale;
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