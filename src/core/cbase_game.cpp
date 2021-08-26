#include "cbase_game.h"

cgame::cgame(API *engineAPI, cbase_gamemode *startGamemode)
{
    this->engineAPI = engineAPI;
    this->currentGamemode = startGamemode;
    this->gameEvents = new EventRegister();

    // Self Managing gameApi
    this->internalGameApi = new gameApi();
    this->internalGameApi->gameMode = this->currentGamemode;
    this->internalGameApi->gameRegister = this->gameEvents;
}

World *cgame::createLoadingWorld(){
    World *tempWorld = new World("PreLoadingScreen", this->internalGameApi);
    tempWorld->entities->push_back(new PreloadScreen(tempWorld->internalWorldApi));
    return tempWorld;
}

void cgame::begin()
{
    this->onBegin();
    this->currentWorld = createLoadingWorld();
    this->currentWorld->onCreate();
}

void cgame::tick()
{
    this->onTick();
    this->currentWorld->onTick();
}

void cgame::quit()
{
    this->onQuit();
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
    virtualConsole::log(std::to_string(this->currentWorld->lights->size()));
    this->engineAPI->renderer->render(this->currentWorld->lights, this->currentWorld->camera);
    this->engineAPI->gui->render(this->currentWorld->guis);
}

cgame::~cgame()
{
    delete this->gameEvents;
    delete this->internalGameApi;
}