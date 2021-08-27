#pragma once
#include <vector>

#include "../model/RawModel.h"
#include "SkyboxShader.h"

// define _CUBE_SIZE_ constant
const static float _CUBE_SIZE_ = 500.0f;

class SkyboxRenderer {
    private:   
        // Std vertices for cubemap
        std::vector<GLfloat> VERTICES{   
            -_CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,
            -_CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,
            -_CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,

            -_CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,
            -_CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            -_CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,
            -_CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,
            -_CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            -_CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,

            _CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,

            -_CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,
            -_CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,
            -_CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,

            -_CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            -_CUBE_SIZE_,  _CUBE_SIZE_,  _CUBE_SIZE_,
            -_CUBE_SIZE_,  _CUBE_SIZE_, -_CUBE_SIZE_,

            -_CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            -_CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_, -_CUBE_SIZE_,
            -_CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_,
            _CUBE_SIZE_, -_CUBE_SIZE_,  _CUBE_SIZE_
        };
    
        std::vector<const char*> TEXTFILES{"right", "left", "top", "bottom", "back", "front"};

        RawModel* cube;
        GLuint texture;
        SkyboxShader* shader;

    public:
        SkyboxRenderer(Loader *loader, glm::mat4 projectionMatrix);
        void render(Camera *camera, glm::vec3 colour);
};