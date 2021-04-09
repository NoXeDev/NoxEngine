#include "RawModel.h"

RawModel::RawModel(GLuint vaoID, GLsizei vertexCount)
{
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}

GLuint RawModel::getVaoID()
{
	return this->vaoID;
}

GLsizei RawModel::getVertexCount()
{
	return this->vertexCount;
}
