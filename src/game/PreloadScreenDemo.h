#pragma once
#include <glew.h>
#include "../entities/Entity.h"
#include "../renderEngine/DisplayManager.h"

class PreloadScreen: public Entity{
    public:
        PreloadScreen(WorldApi *worldApi): Entity(worldApi)
        {
            this->worldApi->worldEvents->SubscribeEvent("onCreate", std::bind(&PreloadScreen::onBegin, this));
        };
        void onBegin(){
            //DisplayManager::updateDisplay();
            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
        }
};