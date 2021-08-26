#include "MasterRenderer.h"

const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000;

const glm::vec3 SKYRGB = glm::vec3(0.5f, 0.5f, 0.5f);

MasterRenderer::MasterRenderer()
{
	enableCulling();
	this->shader->create();
	this->terrainShader->create();
	this->createProjectionMatrix();
	this->renderer = new EntityRenderer(this->shader, this->projectionMatrix);
	this->terrainRenderer = new TerrainRenderer(this->terrainShader, this->projectionMatrix);
}

void MasterRenderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::render(std::vector<Light*> *lights, Camera* camera)
{
	this->prepare();
	//rendering entities
	this->shader->start();
	this->shader->loadSkyColour(SKYRGB.x, SKYRGB.y, SKYRGB.z);
	this->shader->loadLights(lights);
	this->shader->loadViewMatrix(camera);

	this->renderer->render(this->entities);

	this->shader->stop();

	//rendering terrains
	this->terrainShader->start();
	this->terrainShader->loadSkyColour(SKYRGB.x, SKYRGB.y, SKYRGB.z);
	this->terrainShader->loadLights(lights);
	this->terrainShader->loadViewMatrix(camera);

	this->terrainRenderer->render(this->terrains);

	this->terrainShader->stop();

	this->terrains.clear();
	this->entities.clear();

}

void MasterRenderer::cleanUp()
{
	this->shader->cleanUp();
	this->terrainShader->cleanUp();
}

void MasterRenderer::processEntity(ModelEntity *entity)
{
	TexturedModel* entityModel = entity->getModel();
	std::vector<ModelEntity*> *batch;
	if(this->entities.find(entityModel) != this->entities.end()){
		batch = &this->entities.at(entityModel);
	}else {
		batch = new std::vector<ModelEntity*>{};
	}

	if (!batch->empty()) {
		batch->push_back(entity);
	}
	else {
		std::vector<ModelEntity*> newBatch;
		newBatch.push_back(entity);
		this->entities.insert({ entityModel, newBatch });
	}
}

void MasterRenderer::processTerrain(Terrain* terrain)
{
	this->terrains.push_back(terrain);
}

void MasterRenderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(SKYRGB.x, SKYRGB.y, SKYRGB.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::createProjectionMatrix()
{
	float aspectRatio = (float)DisplayManager::getWidth() / (float)DisplayManager::getHeight();
	this->projectionMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}