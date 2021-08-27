#pragma once
#include <vector>
#include <sstream>
#include <glew.h>

#include "../model/RawModel.h"
#include "../textures/TextureData.h"

using namespace std;
class Loader
{
private:
	vector<GLuint> vaos;
	vector<GLuint> vbos;
	vector<GLuint> textures;
	int createVAO();
	void storeDataInAttributeList(GLuint attributeNumber, GLint coordinateSize, std::vector<GLfloat> *data);
	void unbindVAO();
	void bindIndicesBuffer(std::vector<GLint> *indices);
	TextureData* decodeTextureFile(const char *filename);
public:
	RawModel* loadToVAO(
		std::vector<GLfloat> *positions,
		std::vector<GLfloat> *textureCoords,
		std::vector<GLfloat> *normals,
		std::vector<GLint> *indices
	);
	RawModel* loadToVAO(std::vector<GLfloat> *positions, int dimensions);
	void cleanUp();
	int loadTexture(const char* filename);
	int loadCubeMap(std::vector<const char*> textureFiles);
};

