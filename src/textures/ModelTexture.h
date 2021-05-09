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
	GLboolean getTransparency();
	void setTransparency(GLboolean transparency);
	GLboolean getFakeLighting();
	void setFakeLighting(GLboolean fakeLighting);
private:
	GLuint textureID;

	GLfloat shineDamper = 1.0f;
	GLfloat reflectivity = 0.0f;
	GLboolean hasTransparency = false;
	GLboolean useFakeLighting = false;
};

