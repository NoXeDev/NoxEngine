#include "NoxGame.h"

NoxGame::NoxGame(API *engineAPI): cgame(engineAPI, new cbase_gamemode())
{}

void NoxGame::onBegin()
{
    virtualConsole::log("NoxGame has begin");
}

void NoxGame::onTick(){}

void NoxGame::onQuit()
{
    virtualConsole::log("NoxGame exited");
}

void NoxGame::createGameApi()
{
    NoxGameApi myapi;
    myapi.gameRegister = this->getGameEvents();
    myapi.gameMode = this->getCurrentGameMode();
    myapi.printFromGame = std::bind(&NoxGame::printFromGame, this, std::placeholders::_1);
    this->internalGameApi = &myapi;
}

void NoxGame::printFromGame(const char *content)
{
    ostringstream ss;
    ss << "[NoxGame] - " << content;
    virtualConsole::log(ss.str());
}