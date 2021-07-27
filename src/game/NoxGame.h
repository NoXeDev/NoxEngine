#pragma once
#include "../core/cbase_game.h"
#include "../common/cbase.h"
#include "../common/types.h"

class NoxGame : public cgame{
    public:
        NoxGame(API *engineAPI);
    protected:
        void onBegin();
        void onTick();
        void onQuit();
};