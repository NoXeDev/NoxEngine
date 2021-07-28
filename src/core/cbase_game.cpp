#include "cbase_game.h"

cgame::cgame(API *engineAPI, cbase_gamemode *startGamemode)
{
    this->engineAPI = engineAPI;
    this->currentGamemode = startGamemode;
    this->gameEvents = new EventRegister();
}

World *cgame::createLoadingWorld(){
    World *tempWorld = new World("PreLoadingScreen", this->internalGameApi);
    tempWorld->entities->push_back(new PreloadScreen(tempWorld->internalWorldApi));
    return tempWorld;
}

void cgame::onBaseBegin()
{
    this->currentWorld = createLoadingWorld();
    this->currentWorld->onCreate();
}

void cgame::onBaseTick()
{
    this->currentWorld->onTick();
}

void cgame::onBaseQuit()
{
    this->currentWorld->onQuit();
}

void cgame::switchWorld(World *newWorld)
{
    this->currentWorld->onQuit();
    delete this->currentWorld;
    this->currentWorld = newWorld;
    this->currentWorld->onCreate();
}

void cgame::worldRender()
{
    for(Terrain *terrain : *this->currentWorld->terrains)
    {
        this->engineAPI->renderer->processTerrain(terrain);
    }
    for(ModelEntity *entity : *this->currentWorld->modelEntity)
    {
        this->engineAPI->renderer->processEntity(entity);
    }
    this->engineAPI->renderer->render(this->currentWorld->lights->at(0), this->currentWorld->camera);
    this->engineAPI->gui->render(this->currentWorld->guis);
}

cgame::~cgame()
{
    delete this->gameEvents;
    delete this->internalGameApi;
}