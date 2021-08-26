#pragma once
#include "ShaderProgram.h"
#include <glm.hpp>
#include "../entities/Camera.h"
#include "../entities/Light.h"
#include "../utils/Maths.h"

class TerrainShader :public ShaderProgram
{
public:
	TerrainShader();
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera* camera);
	void loadLights(std::vector<Light*> *lights);
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadSkyColour(float r, float g, float b);
	void connectTextureUnits();
protected:
	void bindAttributes();
	void getAllUniformLocations();
private:
	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	std::vector<int> location_lightPosition;
	std::vector<int> location_lightColour;
	int location_shineDamper;
	int location_reflectivity;
	int location_skyColour;
	int location_backgroundTexture;
	int location_rTexture;
	int location_gTexture;
	int location_bTexture;
	int location_blendMap;
};

