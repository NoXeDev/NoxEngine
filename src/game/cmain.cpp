#include "cmain.h"
#include "NoxGame.h"
#include "../core/cbase_world.h"
#include "../common/engineApi.h"
#include <chrono>

void cmain(API* engineAPI)
{
    //creating game Object here
    std::unique_ptr<NoxGame> mygame(new NoxGame(engineAPI));
	
    std::unique_ptr<World> myworld(new World("demo", mygame->internalGameApi));

    //loading files assets (time loading calculation implemented)
	auto start = std::chrono::high_resolution_clock::now();
	std::unique_ptr<RawModel> model(NMloader::loadNMmodel("res/models/dragon.nm", engineAPI->loader));
	std::unique_ptr<RawModel> character(NMloader::loadNMmodel("res/models/character.nm", engineAPI->loader));
	std::unique_ptr<RawModel> grass(NMloader::loadNMmodel("res/models/grass.nm", engineAPI->loader));
	std::unique_ptr<ModelTexture> texture(new ModelTexture(engineAPI->loader->loadTexture("res/materials/stallTexture.png")));
	std::unique_ptr<ModelTexture> grassTexture(new ModelTexture(engineAPI->loader->loadTexture("res/materials/grassTexture.png")));
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::ostringstream ss;
	ss << "Loading time : " << (float)duration.count() / 1000000 << "'s";
	virtualConsole::log(ss.str(), LOGdebug);

	//set textures varaibles
	texture->setShineDamper(10);
	texture->setReflectivity(1);	
	grassTexture->setTransparency(true);
	grassTexture->setFakeLighting(true);

	std::unique_ptr<TerrainTexture> backgroundTexture(new TerrainTexture(engineAPI->loader->loadTexture("res/materials/grass.png")));
	std::unique_ptr<TerrainTexture> rTexture(new TerrainTexture(engineAPI->loader->loadTexture("res/materials/dirt.png")));
	std::unique_ptr<TerrainTexture> gTexture(new TerrainTexture(engineAPI->loader->loadTexture("res/materials/grassFlowers.png")));
	std::unique_ptr<TerrainTexture> bTexture(new TerrainTexture(engineAPI->loader->loadTexture("res/materials/path.png")));

	std::unique_ptr<TerrainTexture> blendMap(new TerrainTexture(engineAPI->loader->loadTexture("res/materials/blendMap.png")));

	//create ingame entity from assets
	std::unique_ptr<TexturedModel> texturedModel(new TexturedModel(model.get(), texture.get()));
	std::unique_ptr<TexturedModel> characterTextured(new TexturedModel(character.get(), texture.get()));
	std::unique_ptr<TexturedModel> grassTexturedModel(new TexturedModel(grass.get(), grassTexture.get()));

	std::unique_ptr<TerrainTexturePack> texturePack(new TerrainTexturePack(backgroundTexture.get(), rTexture.get(), gTexture.get(), bTexture.get()));
	std::unique_ptr<Terrain> terrain(new Terrain(0, 0, engineAPI->loader, texturePack.get(), blendMap.get(), "res/materials/heightmap.png"));


	std::unique_ptr<Player> player(new Player(glm::vec3(200, terrain->getHeightOfTerrain(200, 200), 200), glm::vec3(0, 0, 0)));
	myworld->player = player.get();
	std::unique_ptr<ModelEntity> entity2(new ModelEntity(myworld->internalWorldApi, texturedModel.get(), glm::vec3(500, terrain->getHeightOfTerrain(500, 395), 395), glm::vec3(0, 0, 0), 1));
	std::unique_ptr<ModelEntity> characterEntity(new ModelEntity(myworld->internalWorldApi, characterTextured.get(), glm::vec3(550, 30, 450), glm::vec3(0, 0, 0), 1));

	

	std::unique_ptr<ModelEntity> entity(new ModelEntity(myworld->internalWorldApi, texturedModel.get(), glm::vec3(500, terrain->getHeightOfTerrain(500, 500), 500), glm::vec3(0, 0, 0), 1));
	//std::unique_ptr<Entity> grassEntity(new Entity(grassTexturedModel.get(), glm::vec3(200, 0, 200), 0, 0, 0, 1));

	/// LIGHT SECTION ///
	std::unique_ptr<Light> light(new Light(myworld->internalWorldApi, glm::vec3(0, 10000, -7000), glm::vec3(0, 0, 0), glm::vec3(0.4,0.4,0.4)));
	std::unique_ptr<Light> light2(new Light(myworld->internalWorldApi, glm::vec3(300, terrain->getHeightOfTerrain(300, 200)+5, 200), glm::vec3(0, 0, 0), glm::vec3(2,0,0), glm::vec3(1, 0.01, 0.002)));
	std::unique_ptr<Light> light3(new Light(myworld->internalWorldApi, glm::vec3(200, terrain->getHeightOfTerrain(200, 200)+5, 200), glm::vec3(0, 0, 0), glm::vec3(0,2,2), glm::vec3(1, 0.01, 0.002)));
	////////////////////

    std::vector<ModelEntity*> worldModels = {entity.get(), entity2.get(), characterEntity.get()};
    std::vector<Terrain*> terrainsWorld = {terrain.get()};
    std::vector<Light*> worldLights = {light.get(), light2.get(), light3.get()};
    std::vector<GuiTexture*> guiTextures = {};
    std::vector<Entity*> worldEntities = {};

    *myworld->lights = worldLights;
    *myworld->terrains = terrainsWorld;
    *myworld->guis = guiTextures;
    *myworld->modelEntity = worldModels;
    *myworld->entities = worldEntities;

	mygame->begin();

    mygame->switchWorld(myworld.get());

	myworld->playerSpawn();

    while(true)
    {
        engineAPI->engineTickCallback();

		mygame->tick();
        mygame->worldRender();

        DisplayManager::updateDisplay();
        if(DisplayManager::displayShouldClose() || engineAPI->engineThreadBreaker()){break;};
    }

	mygame->quit();
}