#pragma once
#include <glew.h>
class RawModel
{
public:
	RawModel(GLuint vaoID, GLsizei vertexCount);
	GLuint getVaoID();
	GLsizei getVertexCount();
private:
	GLuint vaoID;
	GLsizei vertexCount;
};

