#pragma once
#include <glew.h>
#include "../entities/Entity.h"

class PreloadScreen: public Entity{
    public:
        PreloadScreen(World *worldContext): Entity()
        {};
        void onTick()
        {
            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
        }
};