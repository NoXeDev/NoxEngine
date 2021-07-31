#pragma once
#include "gameApi.h"
#include "worldApi.h"
#include "../core/virtualConsole.h"
#include "../entities/Player.h"
#include "../guis/GuiTexture.h"
#include "../entities/ModelEntity.h"
#include "../entities/Light.h"
class World {
    public:
        const char *name;
        gameApi *currentGameApi;
        EventRegister *worldEvents;
        std::vector<Terrain*> *terrains;
        std::vector<Entity*> *entities;
        std::vector<ModelEntity*> *modelEntity;
        std::vector<Light*> *lights;
        std::vector<GuiTexture*> *guis;
        WorldApi *internalWorldApi;
        Camera *camera;
        Player *player;
        World(
            const char* name,
            gameApi *currentGameApi,
            std::vector<ModelEntity*> *modelEntity_c = new std::vector<ModelEntity*>(),
            std::vector<Entity*> *entities_c = new std::vector<Entity*>(),
            std::vector<Terrain*> *terrains_c = new std::vector<Terrain*>(),
            std::vector<Light*> *lights_c = new std::vector<Light*>(),
            std::vector<GuiTexture*> *guis_c = new std::vector<GuiTexture*>(),
            Player *player = nullptr
        );
        ~World();

        void playerSpawn();
        void onCreate();
        void onTick();
        void onQuit();
};