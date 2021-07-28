#include "cbase_world.h"

World::World(const char* name,
    gameApi *currentGameApi,
    std::vector<ModelEntity*> *modelEntity_c,
    std::vector<Entity*> *entities_c,
    std::vector<Terrain*> *terrains_c,
    std::vector<Light*> *lights_c,
    std::vector<GuiTexture*> *guis_c
)
{
    this->name = name;
    this->currentGameApi = currentGameApi;
    this->entities = entities_c;
    this->modelEntity = modelEntity_c;
    this->terrains = terrains_c;
    this->lights = lights_c;
    this->guis = guis_c;
    this->worldEvents = new EventRegister();

    //for the moment the engine is not able to leave lights empty, he need light
    if(this->lights->empty())
    {
        this->lights->push_back(new Light(internalWorldApi, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
    }

    //create the world api for all entities
    WorldApi *myapi = new WorldApi();
    myapi->currentGameApi = this->currentGameApi;
    myapi->worldEvents = this->worldEvents;
    myapi->terrains = this->terrains;

    this->internalWorldApi = myapi;

    this->camera = new Camera(this->internalWorldApi);

    //regestering 3 basic events for the world creation
    this->worldEvents->RegisteringEvent("onCreate");
    this->worldEvents->RegisteringEvent("onTick");
    this->worldEvents->RegisteringEvent("onQuit");
}

World::~World()
{
    // This part is for when the engine will load Entities into Raw Ptr
    /*delete this->worldEvents;
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
    delete this->internalWorldApi;*/
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