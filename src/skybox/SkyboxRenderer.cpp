#include "SkyboxRenderer.h"

SkyboxRenderer::SkyboxRenderer(Loader *loader, glm::mat4 projectionMatrix)
{
    this->cube = loader->loadToVAO(&this->VERTICES, 3);
    this->texture = loader->loadCubeMap(this->TEXTFILES);
    this->shader = new SkyboxShader();
    this->shader->create();
    this->shader->start();
    this->shader->loadProjectionMatrix(projectionMatrix);
    this->shader->stop();
}

void SkyboxRenderer::render(Camera *camera)
{
    this->shader->start();
    this->shader->loadViewMatrix(camera);
    glBindVertexArray(this->cube->getVaoID());
    glEnableVertexAttribArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
    glDrawArrays(GL_TRIANGLES, 0, this->cube->getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    this->shader->stop();
}