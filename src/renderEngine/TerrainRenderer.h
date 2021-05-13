#pragma once

#include <glew.h>
#include <glm.hpp>
#include <vector>

#include "../model/TexturedModel.h"
#include "../entities/Entity.h"
#include "../shaders/TerrainShader.h"
#include "../terrain/Terrain.h"

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader* shader, glm::mat4 projectionMatrix);
	void render(std::vector<Terrain*> terrains);
private:
	TerrainShader* shader;
	void prepareTerrrain(Terrain* terrain);
	void unbindTexturedModel();
	void loadModelMatrix(Terrain* terrain);
	void bindTextures(Terrain* terrain);
};

