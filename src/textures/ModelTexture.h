#pragma once
#include <glew.h>
class ModelTexture
{
public:
	ModelTexture(GLuint id);
	GLuint getID();
	GLfloat getShineDamper();
	void setShineDamper(GLfloat shineDamper);
	GLfloat getReflectivity();
	void setReflectivity(GLfloat reflectivity);
private:
	GLuint textureID;

	GLfloat shineDamper = 1.0f;
	GLfloat reflectivity = 0.0f;
};

