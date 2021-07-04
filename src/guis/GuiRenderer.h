#pragma once
#include "../model/RawModel.h"
#include "../renderEngine/Loader.h"
#include "GuiTexture.h"
#include "GuiShader.h"
#include <vector>

class GuiRenderer {
    private:
        RawModel *quad;
        GuiShader *shader;
    public:
        GuiRenderer(Loader* loader);
        void render(std::vector<GuiTexture*> guis);
        void cleanUp();
};