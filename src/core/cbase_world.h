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
            std::vector<Entity*> *entities = new std::vector<Entity*>(),
            std::vector<ModelEntity*> *modelEntity = new std::vector<ModelEntity*>(),
            std::vector<Terrain*> *terrains = new std::vector<Terrain*>(),
            std::vector<Light*> *lights = new std::vector<Light*>(),
            std::vector<GuiTexture*> *guis = new std::vector<GuiTexture*>()
        );
        ~World();

        void playerSpawn(Player *player);
        void onCreate();
        void onTick();
        void onQuit();
};