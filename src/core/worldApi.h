#pragma once
#include "../event/EventRegister.h"
#include "gameApi.h"
#include "../terrain/Terrain.h"

struct WorldApi {
    EventRegister *worldEvents;
    gameApi *currentGameApi;

    //because NoxEngine have no physic engine, we need terrains height for calculate Player Y axis
    std::vector<Terrain*> *terrains;
};