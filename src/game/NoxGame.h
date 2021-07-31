#pragma once
#include "../core/cbase_game.h"
#include "../common/types.h"
#include "../core/virtualConsole.h"

struct NoxGameApi : public gameApi
{
    std::function<void(const char*)> printFromGame;
};

class NoxGame : public cgame{
    public:
        NoxGame(API *engineAPI);
        void printFromGame(const char *content);
        void onBegin();
        void onTick();
        void onQuit();
};