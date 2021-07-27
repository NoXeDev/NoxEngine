#pragma once
#include "../common/cbase.h"
#include "cbase_game.h"

class World {
    public:
        const char *name;
        cgame *gameContextReference;
        EventRegister *worldEvents;
        std::vector<Terrain*> *terrains;
        std::vector<Entity*> *entities;
        std::vector<ModelEntity*> *modelEntity;
        std::vector<Light*> *lights;
        std::vector<GuiTexture*> *guis;
        Camera *camera;
        World(
            const char* name,
            std::vector<Entity*> *entities = new std::vector<Entity*>(),
            std::vector<ModelEntity*> *modelEntity = new std::vector<ModelEntity*>(),
            std::vector<Terrain*> *terrains = new std::vector<Terrain*>(),
            std::vector<Light*> *lights = new std::vector<Light*>(),
            std::vector<GuiTexture*> *guis = new std::vector<GuiTexture*>()
        );
        ~World();
        void preloadSeq(cgame *gameContext);
        void onCreate();
        void onTick();
        void onQuit();
};