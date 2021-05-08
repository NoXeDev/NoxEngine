#include "EntityRenderer.h"
#include "../entities/Entity.h"
#include "../shaders/StaticShader.h"
#include "../utils/Maths.h"

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

void EntityRenderer::render(std::unordered_map<TexturedModel*, std::vector<Entity*>> entities)
{
	for (std::pair<TexturedModel*, std::vector<Entity*>> iter : entities)
	{
		this->prepareTexturedModel(iter.first);
		std::vector<Entity*> batch = iter.second;
		for (Entity* entity : batch) {
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
	this->shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void EntityRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity* entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotX(), entity->getRotY(), entity->getRotZ(), entity->getScale());
	this->shader->loadTransformationMatrix(transformationMatrix);
}