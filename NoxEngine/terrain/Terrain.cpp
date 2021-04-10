#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader* loader, ModelTexture* texture)
{
	this->texture = texture;
	this->x = gridX * this->SIZE;
	this->z = gridZ * this->SIZE;

	this->model = generateTerrain(loader);
}

RawModel* Terrain::generateTerrain(Loader* loader)
{
	int count = this->VERTEX_COUNT * this->VERTEX_COUNT;
	float* vertices = new float[count * 3];
	float* normals = new float[count * 3];
	float* textureCoords = new float[count * 2];
	int* indices = new int[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];

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
	return loader->loadToVAO(vertices, sizeof(*vertices), textureCoords, sizeof(*textureCoords), normals, sizeof(*normals), indices, sizeof(*indices), 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
}

RawModel* Terrain::getModel()
{
	return this->model;
}

ModelTexture* Terrain::getTexture()
{
	return this->texture;
}

float Terrain::getX()
{
	return this->x;
}

float Terrain::getZ()
{
	return this->z;
}
