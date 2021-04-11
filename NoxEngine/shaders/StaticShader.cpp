#include "StaticShader.h"

StaticShader::StaticShader() :ShaderProgram("static")
{

}

void StaticShader::bindAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "textureCoords");
	this->bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations()
{
	this->location_transformationMatrix = this->getUniformLocation("transformationMatrix");
	this->location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	this->location_viewMatrix = this->getUniformLocation("viewMatrix");
	this->location_lightPosition = this->getUniformLocation("lightPosition");
	this->location_lightColour = this->getUniformLocation("lightColour");
	this->location_shineDamper = this->getUniformLocation("shineDamper");
	this->location_reflectivity = this->getUniformLocation("reflectivity");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	this->loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadLight(Light* light)
{
	this->loadVector(location_lightPosition, light->getPositions());
	this->loadVector(location_lightColour, light->getColour());
}

void StaticShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	this->loadFloat(this->location_shineDamper, damper);
	this->loadFloat(this->location_reflectivity, reflectivity);
}


void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	this->loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera* camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	this->loadMatrix(location_viewMatrix, viewMatrix);
}