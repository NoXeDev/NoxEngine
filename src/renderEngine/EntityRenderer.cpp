#include "EntityRenderer.h"
#include "../entities/Entity.h"
#include "../shaders/StaticShader.h"
#include "../utils/Maths.h"
#include "MasterRenderer.h"

#include <glew.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glfw3.h>

EntityRenderer::EntityRenderer(StaticShader *shader, glm::mat4 projectionMatrix)
{
	this->shader = shader;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void EntityRenderer::render(std::unordered_map<TexturedModel*, std::vector<ModelEntity*>> entities)
{
	for (std::pair<TexturedModel*, std::vector<ModelEntity*>> iter : entities)
	{
		this->prepareTexturedModel(iter.first);
		std::vector<ModelEntity*> batch = iter.second;
		for (ModelEntity* entity : batch) {
			this->prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, iter.first->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		this->unbindTexturedModel();
	}
}

void EntityRenderer::prepareTexturedModel(TexturedModel* model)
{
	RawModel *rawModel = model->getRawModel();
	glBindVertexArray(rawModel->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture* texture = model->getTexture();
	if(texture->getTransparency())
	{
		MasterRenderer::disableCulling();
	}
	this->shader->loadFakeLightingVariable(texture->getFakeLighting());
	this->shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void EntityRenderer::unbindTexturedModel()
{
	MasterRenderer::enableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(ModelEntity* entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
	this->shader->loadTransformationMatrix(transformationMatrix);
}