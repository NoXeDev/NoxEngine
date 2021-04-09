#include "Camera.h"
#include <glfw3.h>

Camera::Camera(DisplayManager* display)
{
	this->display = display;
}

void Camera::move()
{
	if (glfwGetKey(this->display->window, GLFW_KEY_W)) {
		position.z -= 0.02f;
	}
	if (glfwGetKey(this->display->window, GLFW_KEY_D)) {
		position.x += 0.02f;
	}
	if (glfwGetKey(this->display->window, GLFW_KEY_A)) {
		position.x -= 0.02f;
	}
	if (glfwGetKey(this->display->window, GLFW_KEY_S)) {
		position.z += 0.02f;
	}
	if (glfwGetKey(this->display->window, GLFW_KEY_SPACE)) {
		position.y += 0.02f;
	}
	if (glfwGetKey(this->display->window, GLFW_KEY_LEFT_CONTROL)) {
		position.y -= 0.02f;
	}
}

glm::vec3 Camera::getPosition()
{
	return this->position;
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
