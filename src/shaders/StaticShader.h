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
	void loadFakeLightingVariable(GLboolean useFake);
protected:
	void bindAttributes();
	void getAllUniformLocations();
private:
	int location_transformationMatrix;
	int location_projectionMatrix;
	int location_viewMatrix;
	int location_lightPosition;
	int location_lightColour;
	int location_shineDamper;
	int location_reflectivity;
	int location_useFakeLighting;
};

