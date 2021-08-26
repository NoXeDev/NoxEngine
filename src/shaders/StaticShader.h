#pragma once
#include "ShaderProgram.h"
#include <glm.hpp>

#include "../entities/Camera.h"
#include "../entities/Light.h"
#include "../utils/Maths.h"
class StaticShader:public ShaderProgram
{
public:
	StaticShader();
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera *camera);
	void loadLights(std::vector<Light*> *lights);
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadFakeLightingVariable(GLboolean useFake);
	void loadSkyColour(float r, float g, float b);
protected:
	void bindAttributes();
	void getAllUniformLocations();
private:
	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	std::vector<int> location_lightPosition;
	std::vector<int> location_lightColour;
	std::vector<float> location_attenuation;
	int location_shineDamper;
	int location_reflectivity;
	int location_useFakeLighting;
	int location_skyColour;
};

