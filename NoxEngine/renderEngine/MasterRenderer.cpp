#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(DisplayManager* display)
{
	this->shader->create();
	this->renderer = new Renderer(display, this->shader);
}

void MasterRenderer::render(Light* sun, Camera* camera)
{
	this->renderer->prepare();
	this->shader->start();
	this->shader->loadLight(sun);
	this->shader->loadViewMatrix(camera);

	this->renderer->render(this->entities);

	this->shader->stop();
	this->entities.clear();

}

void MasterRenderer::cleanUp()
{
	this->shader->cleanUp();
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
