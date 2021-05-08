#pragma once
#include <vector>
#include <sstream>
#include <glew.h>

#include "../model/RawModel.h"

using namespace std;
class Loader
{
private:
	vector<GLuint> vaos;
	vector<GLuint> vbos;
	vector<GLuint> textures;
	int createVAO();
	void storeDataInAttributeList(GLuint attributeNumber, GLint coordinateSize, GLfloat data[], GLsizeiptr size);
	void unbindVAO();
	void bindIndicesBuffer(GLint indices[], GLsizeiptr size);
public:
	RawModel* loadToVAO(
		GLfloat positions[], GLsizeiptr size,
		GLfloat textureCoords[], GLsizei coordsSize,
		GLfloat normals[], GLsizei normalsSize,
		GLint indices[], GLsizeiptr indicesSize, GLsizeiptr indicesCount
	);
	void cleanUp();
	int loadTexture(const char* filename);
};

