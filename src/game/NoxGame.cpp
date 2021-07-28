#include "NoxGame.h"

NoxGame::NoxGame(API *engineAPI): cgame(engineAPI, new cbase_gamemode())
{}

void NoxGame::onBegin()
{
    virtualConsole::log("NoxGame has begin");
    this->onBaseBegin();
}

void NoxGame::onTick(){
    this->onBaseTick();
}

void NoxGame::onQuit()
{
    virtualConsole::log("NoxGame exited");
    this->onBaseQuit();
}

void NoxGame::Init()
{
    NoxGameApi *myapi = new NoxGameApi();
    myapi->gameRegister = this->getGameEvents();
    myapi->gameMode = this->getCurrentGameMode();
    myapi->printFromGame = std::bind(&NoxGame::printFromGame, this, std::placeholders::_1);
    this->internalGameApi = myapi;
}

void NoxGame::printFromGame(const char *content)
{
    ostringstream ss;
    ss << "[NoxGame] - " << content;
    virtualConsole::log(ss.str());
}