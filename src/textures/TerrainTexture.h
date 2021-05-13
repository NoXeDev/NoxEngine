#pragma once
#include <glew.h>

class TerrainTexture {
    private:
        GLuint textureID;

    public:
        TerrainTexture(GLuint textureID){this->textureID = textureID;};
        int getTextureID(){return this->textureID;};
};