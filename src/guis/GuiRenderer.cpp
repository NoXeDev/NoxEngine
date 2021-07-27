#include "GuiRenderer.h"
#include "../utils/Maths.h"
#include <iostream>
GuiRenderer::GuiRenderer(Loader* loader)
{
    std::vector<GLfloat> positions = {-1, 1, -1, -1, 1, 1, 1, -1};
    this->quad = loader->loadToVAO(&positions);
    this->shader = new GuiShader();
    this->shader->create();
}

void GuiRenderer::render(std::vector<GuiTexture*> *guis)
{
    this->shader->start();
    glBindVertexArray(this->quad->getVaoID());
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for(GuiTexture *gui: *guis){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gui->getTexture());

        glm::mat4 matrix = Maths::createTransformationMatrix(gui->getPosition(), gui->getScale());
        this->shader->loadTransformationMatrix(matrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GuiRenderer::cleanUp()
{
    this->shader->cleanUp();
}