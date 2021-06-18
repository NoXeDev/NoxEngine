#include "Maths.h"
#include <gtc/matrix_transform.hpp>

float Maths::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, translation);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
	return matrix;
}

glm::mat4 Maths::createViewMatrix(Camera* camera)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::rotate(matrix, glm::radians(camera->getRotation().x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(camera->getRotation().y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(camera->getRotation().z), glm::vec3(0, 0, 1));
	glm::vec3 cameraPos = camera->getPosition();
	glm::vec3 negativeCameraPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
	matrix = glm::translate(matrix, negativeCameraPos);
	return matrix;
}
