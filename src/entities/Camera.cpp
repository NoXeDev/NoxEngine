#include "Camera.h"
#include "../utils/Mouse.h"
#include <glfw3.h>
#include <iostream>

Camera::Camera()
{
	//reset Mouse cursor
	Mouse::setCursorPositions(glm::vec2(0,0));
	this->positions = glm::vec3(0, 0, 0);
	this->rotation = glm::vec3(0, 0, 0);
}

void Camera::move(glm::vec3 positions)
{
	glm::vec2 rotations = Mouse::getCursorPositions();
	this->rotation.x = rotations.y / 50;
	this->rotation.y = rotations.x / 50;

	this->positions = positions + this->cameraOffset;
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