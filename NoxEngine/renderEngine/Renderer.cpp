#include "Renderer.h"
#include "../entities/Entity.h"
#include "../shaders/StaticShader.h"
#include "../utils/Maths.h"

#include <glew.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glfw3.h>

const float FOV = 70;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000;

Renderer::Renderer(DisplayManager* display, StaticShader *shader)
{
	this->shader = shader;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	this->createProjectionMatrix(display);
	shader->start();
	shader->loadProjectionMatrix(this->projectionMatrix);
	shader->stop();
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(std::unordered_map<TexturedModel*, std::vector<Entity*>> entities)
{
	for (std::pair<TexturedModel*, std::vector<Entity*>> iter : entities)
	{
		prepareTexturedModel(iter.first);
		std::vector<Entity*> batch = iter.second;
		for (Entity* entity : batch) {
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, iter.first->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void Renderer::prepareTexturedModel(TexturedModel* model)
{
	RawModel rawModel = model->getRawModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture texture = model->getTexture();
	this->shader->loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model->getTexture().getID());
}

void Renderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Renderer::prepareInstance(Entity* entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotX(), entity->getRotY(), entity->getRotZ(), entity->getScale());
	shader->loadTransformationMatrix(transformationMatrix);
}

void Renderer::createProjectionMatrix(DisplayManager* display)
{
	float aspectRatio = (float)display->getWidth() / (float)display->getHeight();
	projectionMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}