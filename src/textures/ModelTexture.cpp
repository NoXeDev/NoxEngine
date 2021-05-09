#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint id)
{
	this->textureID = id;
}

GLboolean ModelTexture::getFakeLighting()
{
	return this->useFakeLighting;
}

void ModelTexture::setFakeLighting(GLboolean fakeLighting)
{
	this->useFakeLighting = fakeLighting;
}

GLboolean ModelTexture::getTransparency()
{
	return this->hasTransparency;
}

void ModelTexture::setTransparency(GLboolean transparency)
{
	this->hasTransparency = transparency;
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
