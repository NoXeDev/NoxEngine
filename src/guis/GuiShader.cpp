#include "GuiShader.h"

GuiShader::GuiShader(): ShaderProgram("Gui")
{}

void GuiShader::loadTransformationMatrix(glm::mat4 matrix)
{
    this->loadMatrix(this->location_transformationMatrix, matrix);
}

void GuiShader::getAllUniformLocations()
{
    this->location_transformationMatrix = this->getUniformLocation("transformationMatrix");
}

void GuiShader::bindAttributes()
{
    this->bindAttribute(0, "position");
}