#include "Maths.h"
#include <gtc/matrix_transform.hpp>

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
