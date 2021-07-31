#pragma once
#include "../game/PreloadScreenDemo.h"
#include "cbase_gamemode.h"
#include "cbase_world.h"
#include "../common/engineApi.h"

class cgame
{
    public:
        cgame(API *engineAPI, cbase_gamemode *startGamemode);
        ~cgame();
        
        World* getCurrentWorld(){
            return this->currentWorld;
        }
        void switchWorld(World *newWorld);
        cbase_gamemode* getCurrentGameMode(){
            return this->currentGamemode;
        }
        EventRegister* getGameEvents(){
            return this->gameEvents;
        }
        void worldRender();
        gameApi *internalGameApi;
        void begin();
        void tick();
        void quit();

        virtual void onBegin() = 0;
        virtual void onTick() = 0;
        virtual void onQuit() = 0;
    private:
        World *currentWorld;
        cbase_gamemode *currentGamemode;
        EventRegister *gameEvents;
        World* createLoadingWorld();
        API *engineAPI;
};