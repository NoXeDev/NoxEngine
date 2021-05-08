#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint id)
{
	this->textureID = id;
}

GLuint ModelTexture::getID()
{
	return this->textureID;
}

GLfloat ModelTexture::getShineDamper()
{
	return this->shineDamper;
}

void ModelTexture::setShineDamper(GLfloat shineDamper)
{
	this->shineDamper = shineDamper;
}

GLfloat ModelTexture::getReflectivity()
{
	return this->reflectivity;
}

void ModelTexture::setReflectivity(GLfloat reflectivity)
{
	this->reflectivity = reflectivity;
}
