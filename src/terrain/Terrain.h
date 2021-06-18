#pragma once
#include "../model/RawModel.h"
#include "../textures/ModelTexture.h"
#include "../renderEngine/Loader.h"
#include "../textures/TerrainTexture.h"
#include "../textures/TerrainTexturePack.h"
#include <glm.hpp>
class Terrain
{
private:
	const float SIZE = 800;
	const float MAX_HEIGHT = 40;
	const float MAX_PIXEL_COLOUR = 256 * 256 * 256;

	int heightMapWidth, heightMapHeight;

	float x;
	float z;
	std::vector<std::vector<float>> heights;

	RawModel *model;
	TerrainTexturePack *texturePack;
	TerrainTexture *blendMap;

	RawModel* generateTerrain(Loader* loader, const char *heightMap);
	float getHeight(int x, int z, unsigned char * buffer);
	glm::vec3 calculateNormal(int x, int z, unsigned char * buffer);

public:
	Terrain(int gridX, int gridZ, Loader *loader, TerrainTexturePack *texturePack, TerrainTexture *blendMap, const char *heightMap);

	RawModel* getModel();
	TerrainTexturePack* getTexturePack();
	TerrainTexture* getBlendMap();
	float getX();
	float getZ();
	float getHeightOfTerrain(float worldX, float worldZ);
};

