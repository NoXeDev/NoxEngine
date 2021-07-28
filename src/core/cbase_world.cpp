#include "cbase_world.h"

World::World(const char* name,
    gameApi *currentGameApi,
    std::vector<Entity*> *entities,
    std::vector<ModelEntity*> *modelEntity,
    std::vector<Terrain*> *terrains,
    std::vector<Light*> *lights,
    std::vector<GuiTexture*> *guis
)
{
    this->name = name;
    this->currentGameApi = currentGameApi;
    this->entities = entities;
    this->modelEntity = modelEntity;
    this->terrains = terrains;
    this->lights = lights;
    this->guis = guis;
    this->worldEvents = new EventRegister();

    //create the world api for all entities
    WorldApi myapi;
    myapi.currentGameApi = this->currentGameApi;
    myapi.worldEvents = this->worldEvents;
    myapi.terrains = this->terrains;

    this->internalWorldApi = &myapi;

    this->camera = new Camera(this->internalWorldApi);

    //regestering 3 basic events for the world creation
    this->worldEvents->RegisteringEvent("onCreate");
    this->worldEvents->RegisteringEvent("onTick");
    this->worldEvents->RegisteringEvent("onQuit");

    //apply world api into all entities

}

World::~World()
{
    delete this->worldEvents;
    for(Entity* entity : *this->entities){
        delete entity;
    }
    for(ModelEntity* entityModel : *this->modelEntity){
        delete entityModel;
    }
    for(Terrain* terrain : *this->terrains){
        delete terrain;
    }
    for(Light* light : *this->lights){
        delete light;
    }
    delete this->entities;
    delete this->terrains;
    delete this->lights;
    delete this->camera;
    delete this->internalWorldApi;
}

void World::onCreate()
{
    virtualConsole::log("World created !");
    this->worldEvents->fire("onCreate");
}

void World::onTick()
{
    this->worldEvents->fire("onTick");
}

void World::onQuit()
{
    virtualConsole::log("World Quited !");
    this->worldEvents->fire("onQuit");
}

void World::playerSpawn(Player *player)
{
    this->player = player;
    this->player->attachCameraToPlayer(this->camera);
}