#pragma once
#include "../model/RawModel.h"
#include "../textures/ModelTexture.h"
#include "../renderEngine/Loader.h"
#include "../textures/TerrainTexture.h"
#include "../textures/TerrainTexturePack.h"
class Terrain
{
private:
	const float SIZE = 800;
	const float VERTEX_COUNT = 128;

	float x;
	float z;

	RawModel *model;
	TerrainTexturePack *texturePack;
	TerrainTexture *blendMap;

	RawModel* generateTerrain(Loader* loader);

public:
	Terrain(int gridX, int gridZ, Loader *loader, TerrainTexturePack *texturePack, TerrainTexture *blendMap);

	RawModel* getModel();
	TerrainTexturePack* getTexturePack();
	TerrainTexture* getBlendMap();
	float getX();
	float getZ();
};

