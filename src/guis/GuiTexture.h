#pragma once
#include <glew.h>
#include <glm.hpp>
class GuiTexture {
    public:
        GuiTexture(GLint texture, glm::vec2 positions, glm::vec2 scale);
        GLint getTexture();
        glm::vec2 getPosition();
        glm::vec2 getScale();
        glm::vec2 getTextureResolution();
    private:
        GLint texture;
        glm::vec2 position;
        glm::vec2 scale;
};