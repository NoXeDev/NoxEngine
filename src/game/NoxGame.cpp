#include "NoxGame.h"

NoxGame::NoxGame(API *engineAPI): cgame(engineAPI, new cbase_gamemode())
{
}

void NoxGame::onBegin()
{
    virtualConsole::log("NoxGame has begin");
}

void NoxGame::onTick(){
}

void NoxGame::onQuit()
{
    virtualConsole::log("NoxGame exited");
}