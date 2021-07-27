#pragma once
#include <glew.h>
#include "../game/PreloadScreenDemo.h"
#include "cbase_gamemode.h"

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
    private:
        World *currentWorld;
        cbase_gamemode *currentGamemode;
        EventRegister *gameEvents;
        World* createLoadingWorld();
        API *engineAPI;
    protected:
        virtual void onBegin();
        virtual void onTick();
        virtual void onQuit();
};