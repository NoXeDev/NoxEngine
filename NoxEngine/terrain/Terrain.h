#pragma once
#include "../model/RawModel.h"
#include "../textures/ModelTexture.h"
#include "../renderEngine/Loader.h"
class Terrain
{
private:
	const float SIZE = 800;
	const float VERTEX_COUNT = 128;

	float x;
	float z;

	RawModel *model;
	ModelTexture *texture;

	RawModel* generateTerrain(Loader* loader);

	RawModel* getModel();
	ModelTexture* getTexture();
	float getX();
	float getZ();

public:
	Terrain(int gridX, int gridZ, Loader *loader, ModelTexture *texture);
};
