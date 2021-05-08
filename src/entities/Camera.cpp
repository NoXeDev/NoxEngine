#include "Camera.h"
#include <glfw3.h>

Camera::Camera(glm::vec3 positions)
{
	this->positions = positions;
}

void Camera::move()
{
	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_W)) {
		positions.z -= 0.5f;
	}
	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_D)) {
		positions.x += 0.5f;
	}
	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_A)) {
		positions.x -= 0.5f;
	}
	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_S)) {
		positions.z += 0.5f;
	}
	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_SPACE)) {
		positions.y += 0.5f;
	}
	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_LEFT_CONTROL)) {
		positions.y -= 0.5f;
	}
}

glm::vec3 Camera::getPosition()
{
	return this->positions;
}

float Camera::getPitch()
{
	return this->pitch;
}

float Camera::getYaw()
{
	return this->yaw;
}

float Camera::getRoll()
{
	return this->roll;
}
