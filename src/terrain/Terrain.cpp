#include "Terrain.h"
#include <iostream>

Terrain::Terrain(int gridX, int gridZ, Loader* loader, TerrainTexturePack *texturePack, TerrainTexture *blendMap)
{
	this->texturePack = texturePack;
	this->blendMap = blendMap;
	this->x = gridX * this->SIZE;
	this->z = gridZ * this->SIZE;

	this->model = generateTerrain(loader);
}

RawModel* Terrain::generateTerrain(Loader* loader)
{
	const int count = this->VERTEX_COUNT * this->VERTEX_COUNT;
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
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
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
	return loader->loadToVAO(&vertices[0], vertices.size() * sizeof(float), &textureCoords[0], textureCoords.size() * sizeof(float), &normals[0], normals.size() * sizeof(float), &indices[0], indices.size() * sizeof(float), indices.size());
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
