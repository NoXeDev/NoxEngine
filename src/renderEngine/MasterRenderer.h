#pragma once
#include "../shaders/StaticShader.h"
#include "EntityRenderer.h"
#include "DisplayManager.h"
#include "../model/TexturedModel.h"
#include "../entities/ModelEntity.h"
#include "../entities/Light.h"
#include "../entities/Camera.h"
#include "../shaders/TerrainShader.h"
#include "../renderEngine/TerrainRenderer.h"
#include "../skybox/SkyboxRenderer.h"

#include <fstream>
#include <unordered_map>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class MasterRenderer
{
private:
	StaticShader* shader = new StaticShader();
	EntityRenderer* renderer;

	TerrainShader* terrainShader = new TerrainShader();
	TerrainRenderer* terrainRenderer;

	std::unordered_map<TexturedModel*, std::vector<ModelEntity*>> entities;
	std::vector<Terrain*> terrains;
	void createProjectionMatrix();
	glm::mat4 projectionMatrix;
	SkyboxRenderer *skyboxRenderer;

public:
	MasterRenderer(Loader *loader);
	void render(std::vector<Light*> *lights, Camera *camera);
	void cleanUp();
	void processEntity(ModelEntity *entity);
	void processTerrain(Terrain* terrain);
	void prepare();
	static void enableCulling();
	static void disableCulling();
};

