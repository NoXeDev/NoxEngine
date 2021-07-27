#include "cbase_world.h"

World::World(const char* name,
    std::vector<Entity*> *entities,
    std::vector<ModelEntity*> *modelEntity,
    std::vector<Terrain*> *terrains,
    std::vector<Light*> *lights,
    std::vector<GuiTexture*> *guis
)
{
    this->name = name;
    this->entities = entities;
    this->modelEntity = modelEntity;
    this->terrains = terrains;
    this->lights = lights;
    this->guis = guis;
    this->worldEvents = new EventRegister();
    this->camera = new Camera(this);

    //regestering 3 basic events for the world creation
    this->worldEvents->RegisteringEvent("onCreate");
    this->worldEvents->RegisteringEvent("onTick");
    this->worldEvents->RegisteringEvent("onQuit");
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

void World::preloadSeq(cgame *gameContext)
{
    this->gameContextReference = gameContext;
    
    //set world context into all entities
    for(Entity *entity : *this->entities){
        entity->setWorldContext(this);
    }
    for(ModelEntity *model : *this->modelEntity)
    {
        model->setWorldContext(this);
    }
    for(Light *light : *this->lights)
    {
        light->setWorldContext(this);
    }
}