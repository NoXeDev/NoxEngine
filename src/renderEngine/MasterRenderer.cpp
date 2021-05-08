#include "MasterRenderer.h"

const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000;

MasterRenderer::MasterRenderer()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	this->shader->create();
	this->terrainShader->create();
	this->createProjectionMatrix();
	this->renderer = new EntityRenderer(this->shader, this->projectionMatrix);
	this->terrainRenderer = new TerrainRenderer(this->terrainShader, this->projectionMatrix);
}

void MasterRenderer::render(Light* sun, Camera* camera)
{
	this->prepare();
	//rendering entities
	this->shader->start();
	this->shader->loadLight(sun);
	this->shader->loadViewMatrix(camera);

	this->renderer->render(this->entities);

	this->shader->stop();

	//rendering terrains
	this->terrainShader->start();
	this->terrainShader->loadLight(sun);
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

void MasterRenderer::processEntity(Entity *entity)
{
	TexturedModel* entityModel = entity->getModel();
	std::vector<Entity*> *batch;
	try {
		batch = &this->entities.at(entityModel);
	}
	catch(const std::out_of_range& oor){
		batch = new std::vector<Entity*>{};
	}

	if (!batch->empty()) {
		batch->push_back(entity);
	}
	else {
		std::vector<Entity*> newBatch;
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
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::createProjectionMatrix()
{
	float aspectRatio = (float)DisplayManager::getWidth() / (float)DisplayManager::getHeight();
	this->projectionMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}