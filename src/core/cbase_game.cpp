#include "cbase_game.h"

cgame::cgame(API *engineAPI, cbase_gamemode *startGamemode)
{
    this->engineAPI = engineAPI;
    this->currentWorld = createLoadingWorld();
    this->currentGamemode = startGamemode;
    this->gameEvents = new EventRegister();
}

World *cgame::createLoadingWorld(){
    World *tempWorld = new World("PreLoadingScreen", this->internalGameApi, nullptr);
    tempWorld->entities->push_back(new PreloadScreen(this->currentWorld->internalWorldApi));
    return tempWorld;
}

void cgame::onBegin()
{
    this->currentWorld->onCreate();
}

void cgame::onTick()
{
    this->currentWorld->onTick();
}

void cgame::onQuit()
{
    this->currentWorld->onQuit();
}

void cgame::switchWorld(World *newWorld)
{
    this->currentWorld->onQuit();
    this->currentWorld->~World();
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