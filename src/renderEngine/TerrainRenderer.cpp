#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader* shader, glm::mat4 projectionMatrix)
{
	this->shader = shader;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void TerrainRenderer::render(std::vector<Terrain*> terrains)
{
	for (Terrain* terrain : terrains)
	{
		this->prepareTerrrain(terrain);
		this->loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		this->unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrrain(Terrain* terrain)
{
	RawModel* rawModel = terrain->getModel();
	glBindVertexArray(rawModel->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture* texture = terrain->getTexture();
	this->shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void TerrainRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain* terrain)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(glm::vec3(terrain->getX(), 0, terrain->getZ()), 0, 0, 0, 1);
	this->shader->loadTransformationMatrix(transformationMatrix);
}