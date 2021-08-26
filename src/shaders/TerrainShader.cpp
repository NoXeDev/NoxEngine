#include "TerrainShader.h"
#include <iostream>

#ifndef MAX_LIGHTS
#define MAX_LIGHTS 4
#endif

TerrainShader::TerrainShader() :ShaderProgram("terrain")
{

}

void TerrainShader::bindAttributes()
{
	this->bindAttribute(0, "position");
	this->bindAttribute(1, "textureCoords");
	this->bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations()
{
	this->location_transformationMatrix = this->getUniformLocation("transformationMatrix");
	this->location_projectionMatrix = this->getUniformLocation("projectionMatrix");
	this->location_viewMatrix = this->getUniformLocation("viewMatrix");
	/*this->location_lightPosition = this->getUniformLocation("lightPosition");
	this->location_lightColour = this->getUniformLocation("lightColour");*/
	this->location_shineDamper = this->getUniformLocation("shineDamper");
	this->location_reflectivity = this->getUniformLocation("reflectivity");
	this->location_skyColour = this->getUniformLocation("skyColour");
	this->location_backgroundTexture = this->getUniformLocation("backgroundTexture");
	this->location_rTexture = this->getUniformLocation("rTexture");
	this->location_gTexture = this->getUniformLocation("gTexture");
	this->location_bTexture = this->getUniformLocation("bTexture");
	this->location_blendMap = this->getUniformLocation("blendMap");

	this->location_lightPosition = std::vector<int>(MAX_LIGHTS);
	this->location_lightColour = std::vector<int>(MAX_LIGHTS);
	this->location_attenuation = std::vector<float>(MAX_LIGHTS);
	for(int i = 0 ; i < MAX_LIGHTS ; i++)
	{
		std::string str1 = "lightPosition[" + std::to_string(i);
		std::string str2 = "lightColour[" + std::to_string(i);
		std::string str3 = "attenuation[" + std::to_string(i);
		str1 += "]";
		str2 += "]";
		str3 += "]";
		this->location_lightPosition[i] = this->getUniformLocation(str1.c_str());
		this->location_lightColour[i] = this->getUniformLocation(str2.c_str());
		this->location_attenuation[i] = this->getUniformLocation(str3.c_str());
	}
}

void TerrainShader::connectTextureUnits()
{
	this->loadInt(location_backgroundTexture, 0);
	this->loadInt(location_rTexture, 1);
	this->loadInt(location_gTexture, 2);
	this->loadInt(location_bTexture, 3);
	this->loadInt(location_blendMap, 4);
}

void TerrainShader::loadSkyColour(float r, float g, float b)
{
	this->loadVector(location_skyColour, glm::vec3(r,g,b));
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix)
{
	this->loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadLights(std::vector<Light*> *lights)
{
	for(int i=0 ; i < MAX_LIGHTS ; i++)
	{
		if(i<lights->size())
		{
			this->loadVector(location_lightPosition[i], lights->at(i)->getPosition());
			this->loadVector(location_lightColour[i], lights->at(i)->getColour());
			this->loadVector(location_attenuation[i], lights->at(i)->getAttenuation());
		}
		else 
		{
			this->loadVector(location_lightPosition[i], glm::vec3(0, 0, 0));
			this->loadVector(location_lightColour[i], glm::vec3(0, 0, 0));
			this->loadVector(location_attenuation[i], glm::vec3(1, 0, 0));
		}
	}
}

void TerrainShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	this->loadFloat(this->location_shineDamper, damper);
	this->loadFloat(this->location_reflectivity, reflectivity);
}


void TerrainShader::loadProjectionMatrix(glm::mat4 matrix)
{
	this->loadMatrix(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(Camera* camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	this->loadMatrix(location_viewMatrix, viewMatrix);
}