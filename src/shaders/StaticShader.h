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
	void loadLight(Light *light);
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
protected:
	void bindAttributes();
	void getAllUniformLocations();
private:
	int location_transformationMatrix = NULL;
	int location_projectionMatrix = NULL;
	int location_viewMatrix = NULL;
	int location_lightPosition = NULL;
	int location_lightColour = NULL;
	int location_shineDamper = NULL;
	int location_reflectivity = NULL;
};

