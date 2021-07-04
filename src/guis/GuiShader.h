#pragma once
#include "../shaders/ShaderProgram.h"
#include <glm.hpp>

class GuiShader: public ShaderProgram
{
    public:
        GuiShader();
        void loadTransformationMatrix(glm::mat4 matrix);
    protected:
        void getAllUniformLocations();
        void bindAttributes();
    private:
        int location_transformationMatrix;
};