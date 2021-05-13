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

	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_LEFT)) {
		rotation.y -= 1;
	}

	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_RIGHT)) {
		rotation.y += 1;
	}

	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_UP)) {
		rotation.x -= 1;
	}

	if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_DOWN)) {
		rotation.x += 1;
	}
}

glm::vec3 Camera::getPosition()
{
	return this->positions;
}

glm::vec3 Camera::getRotation()
{
	return this->rotation;
}