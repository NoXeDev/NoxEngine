#include "GuiTexture.h"

GuiTexture::GuiTexture(GLint texture, glm::vec2 positions, glm::vec2 scale)
{
    this->texture = texture;
    this->position = positions;
    this->scale = scale;
}

GLint GuiTexture::getTexture()
{
    return this->texture;
}

glm::vec2 GuiTexture::getPosition()
{
    return this->position;
}

glm::vec2 GuiTexture::getScale()
{
    return this->scale;
}