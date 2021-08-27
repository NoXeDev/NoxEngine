#pragma once
#include "../shaders/ShaderProgram.h"
#include "../entities/Camera.h"
#include "../utils/Maths.h"

#include <gtc/matrix_transform.hpp>

class SkyboxShader : public ShaderProgram
{
    public:
        SkyboxShader();
        void loadProjectionMatrix(glm::mat4 matrix);
        void loadViewMatrix(Camera *camera);
        void loadFogColour(glm::vec3 colour);
    protected:
        void bindAttributes();
	    void getAllUniformLocations(); 
    private:
        int location_projectionMatrix;
	    int location_viewMatrix;
        int location_fogColour;

        float rotation = 0;
        const float ROTATE_SPEED = 1.0f;
};