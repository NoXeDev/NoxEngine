#include "Terrain.h"
#include "../utils/Maths.h"
#include <iostream>
#include <SOIL2.h>
#include <math.h>

Terrain::Terrain(int gridX, int gridZ, Loader* loader, TerrainTexturePack *texturePack, TerrainTexture *blendMap, const char *heightMap)
{
	this->texturePack = texturePack;
	this->blendMap = blendMap;
	this->x = gridX * this->SIZE;
	this->z = gridZ * this->SIZE;

	this->model = generateTerrain(loader, heightMap);
}

RawModel* Terrain::generateTerrain(Loader* loader, const char *heightMap)
{
	// Loading Height map but not with the loadTexture function. We are going to load image raw buffer

	unsigned char *heightMapBuff = SOIL_load_image(heightMap, &this->heightMapWidth, &this->heightMapHeight, 0, SOIL_LOAD_RGBA);
	int VERTEX_COUNT = this->heightMapHeight;
	//allocate vector memory for heights
	this->heights = std::vector<std::vector<float>>(VERTEX_COUNT, std::vector<float>(VERTEX_COUNT));

	const int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<int> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));


	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			float height = this->getHeight(j, i, heightMapBuff);
			this->heights[j][i] = height;
			vertices[vertexPointer * 3 + 1] = height;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			glm::vec3 normal = this->calculateNormal(j, i, heightMapBuff);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	SOIL_free_image_data(heightMapBuff);
	return loader->loadToVAO(&vertices, &textureCoords, &normals, &indices);
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ)
{
	float terrainX = worldX - this->x;
	float terrainZ = worldZ - this->z;
	float gridSquareSize = this->SIZE / ((float)this->heights.size() - 1);
	int gridX = (int) glm::floor(terrainX / gridSquareSize);
	int gridZ = (int) glm::floor(terrainZ / gridSquareSize);
	if(gridX >= this->heights.size() - 1 || gridZ >= this->heights.size() - 1 || gridX < 0 || gridZ < 0){
		return 0;
	}
	float xCoord = fmod(terrainX, gridSquareSize)/gridSquareSize;
	float zCoord = fmod(terrainZ, gridSquareSize)/gridSquareSize;
	float answer;
	if(xCoord <= (1-zCoord)){
		answer = Maths::barryCentric(glm::vec3(0, this->heights[gridX][gridZ], 0), glm::vec3(1, this->heights[gridX + 1][gridZ], 0), 
		glm::vec3(0, this->heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));

	}else {
		answer = Maths::barryCentric(glm::vec3(1, this->heights[gridX + 1][gridZ], 0), glm::vec3(1, this->heights[gridX + 1][gridZ + 1], 1), 
		glm::vec3(0, this->heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	return answer;
}

RawModel* Terrain::getModel()
{
	return this->model;
}

TerrainTexturePack* Terrain::getTexturePack()
{
	return this->texturePack;
}

TerrainTexture* Terrain::getBlendMap()
{
	return this->blendMap;
}

float Terrain::getX()
{
	return this->x;
}

float Terrain::getZ()
{
	return this->z;
}

float Terrain::getHeight(int x, int z, unsigned char * buffer)
{
	if(x<0 || x>=this->heightMapHeight || z<0 || z>=this->heightMapHeight){
		return 0;
	}

	GLsizei index = 4 * (z * this->heightMapWidth + x);

	//this line is returning a binary integer value from each color
	float RGB = (static_cast<int>(buffer[index + 3]) << 24) | (static_cast<int>(buffer[index + 0]) << 16) | (static_cast<int>(buffer[index + 1]) << 8) | (static_cast<int>(buffer[index + 2]) << 0);
	/////////////////////////////////////////////
	RGB += MAX_PIXEL_COLOUR/2.0f;
	RGB /= MAX_PIXEL_COLOUR/2.0f;
	RGB *= MAX_HEIGHT;
	return RGB;
}

glm::vec3 Terrain::calculateNormal(int x, int z, unsigned char * buffer)
{
	float heightL = this->getHeight(x-1, z, buffer);
	float heightR = this->getHeight(x+1, z, buffer);
	float heightD = this->getHeight(x, z-1, buffer);
	float heightU = this->getHeight(x, z+1, buffer);

	glm::vec3 normal = glm::vec3(heightL-heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);
	return normal;
}