#include "Loader.h"
#include <vector>
#include <glew.h>
#include <iostream>
#include <SOIL2.h>

#include "../model/RawModel.h"
#include "../common/const.h"
#include "../core/errorHandler.h"

using namespace std;

RawModel* Loader::loadToVAO(
	std::vector<GLfloat> *positions,
	std::vector<GLfloat> *textureCoords,
	std::vector<GLfloat> *normals,
	std::vector<GLint> *indices
)
{
	GLuint vaoID = this->createVAO();
	this->bindIndicesBuffer(indices);
	this->storeDataInAttributeList(0, 3, positions);
	this->storeDataInAttributeList(1, 2, textureCoords);
	this->storeDataInAttributeList(2, 3, normals);
	this->unbindVAO();
	return new RawModel(vaoID, indices->size());
}

RawModel* Loader::loadToVAO(std::vector<GLfloat> *positions, int dimensions)
{
	GLint vaoID = createVAO();
	this->storeDataInAttributeList(0, dimensions, positions);
	unbindVAO();
	return new RawModel(vaoID, positions->size()/dimensions);
}

TextureData* Loader::decodeTextureFile(const char *filename)
{
	int width, height;
	unsigned char *texture = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	if (texture == nullptr) {
		std::ostringstream ss;
		ss << "Texture loading fatal error : " << SOIL_last_result() << filename;
		errorHandler::fatal(ss.str());
	}

	// Creating texture data struct
	TextureData *res = new TextureData();
	res->width = width;
	res->height = height;
	res->buffer = texture;

	return res;
}

int Loader::loadCubeMap(std::vector<const char*> textureFiles)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for(int i = 0 ; i < textureFiles.size() ; i++)
	{
		ostringstream ss;
		ss << "res/materials/cubemap/" << textureFiles.at(i) << ".png";
		TextureData *data = decodeTextureFile(ss.str().c_str());

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data->width, data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->buffer);
		SOIL_free_image_data(data->buffer);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	this->textures.push_back(textureID);

	return textureID;
}

int Loader::loadTexture(const char* filename)
{
	GLuint textureID;
	int width, height;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *texture = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	if (texture == nullptr) {
		std::ostringstream ss;
		ss << "Texture loading fatal error : " << SOIL_last_result() << filename;
		errorHandler::fatal(ss.str());
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(texture);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
	
	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//add texture to vector
	this->textures.push_back(textureID);
	
	return textureID;
}

void Loader::cleanUp()
{
	for (GLuint vao : this->vaos) {
		glDeleteVertexArrays(1, &vao);
	}
	for (GLuint vbo : this->vbos) {
		glDeleteBuffers(1, &vbo);
	}
	for (GLuint texture : this->textures) {
		glDeleteTextures(1, &texture);
	}
}

int Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	this->vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, GLint coordinateSize, std::vector<GLfloat> *data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	this->vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data->size()*sizeof(GLfloat), &data->front(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void * )0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<GLint> *indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	this->vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()*sizeof(GLint), &indices->front(), GL_STATIC_DRAW);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}
