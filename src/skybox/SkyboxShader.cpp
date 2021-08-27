#include "SkyboxShader.h"

SkyboxShader::SkyboxShader() : ShaderProgram("skybox"){}

void SkyboxShader::bindAttributes()
{
    this->bindAttribute(0, "position");
}

void SkyboxShader::getAllUniformLocations()
{
    this->location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	this->location_viewMatrix = this->getUniformLocation("viewMatrix");
    this->location_fogColour = this->getUniformLocation("fogColour");
}

void SkyboxShader::loadFogColour(glm::vec3 colour)
{
    this->loadVector(this->location_fogColour, colour);
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 matrix)
{
    this->loadMatrix(location_projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(Camera* camera)
{
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    this->rotation += ROTATE_SPEED * DisplayManager::getFrameTimeSeconds();
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0, 1, 0));
	this->loadMatrix(location_viewMatrix, viewMatrix);
}