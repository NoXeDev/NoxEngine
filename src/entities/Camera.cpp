#include "Camera.h"
#include <glfw3.h>

Camera::Camera(glm::vec3 positions)
{
	this->positions = positions;
}

void Camera::move()
{

}

glm::vec3 Camera::getPosition()
{
	return this->positions;
}

glm::vec3 Camera::getRotation()
{
	return this->rotation;
}

void Camera::setPosition(glm::vec3 position)
{
	this->positions = position;
}

void Camera::setRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}