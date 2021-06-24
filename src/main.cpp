#include <iostream>
#ifndef _DEBUG
#include <Windows.h>
#endif

#include <glew.h>
#include <glfw3.h>
#include <array>
#include <fstream>
#include <chrono>
#include <memory>

#include "renderEngine/DisplayManager.h"
#include "renderEngine/Loader.h"
#include "model/RawModel.h"
#include "textures/ModelTexture.h"
#include "model/TexturedModel.h"
#include "entities/Entity.h"
#include "entities/Camera.h"
#include "renderEngine/NMloader.h"
#include "entities/Light.h"
#include "renderEngine/MasterRenderer.h"
#include "entities/Player.h"

int fatalError(const char* message) {
	std::cout << message << std::endl;
	glfwTerminate();

	return EXIT_FAILURE;
}
#ifndef _DEBUG
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){
#else
int main(){
#endif
	//Init GLFW 
	if (!glfwInit()) { return fatalError("[ERROR] - Initialise GLFW failed"); }

	//Window creation
	DisplayManager::createDisplay();

	//Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { return fatalError("[ERROR] - Initialise GLEW failed"); }

	//create loading stuff
	std::unique_ptr<Loader> loader(new Loader());
	std::unique_ptr<MasterRenderer> renderer(new MasterRenderer());

	//loading files assets (time loading calculation implemented)
	auto start = std::chrono::high_resolution_clock::now();
	std::unique_ptr<RawModel> model(NMloader::loadNMmodel("res/models/dragon.nm", loader.get()));
	std::unique_ptr<RawModel> grass(NMloader::loadNMmodel("res/models/grass.nm", loader.get()));
	std::unique_ptr<ModelTexture> texture(new ModelTexture(loader->loadTexture("res/materials/stallTexture.png")));
	std::unique_ptr<ModelTexture> grassTexture(new ModelTexture(loader->loadTexture("res/materials/grassTexture.png")));
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Loading time : " << (float)duration.count() / 1000000 << "'s" << std::endl;

	//set textures varaibles
	texture->setShineDamper(10);
	texture->setReflectivity(1);	
	grassTexture->setTransparency(true);
	grassTexture->setFakeLighting(true);

	std::unique_ptr<TerrainTexture> backgroundTexture(new TerrainTexture(loader->loadTexture("res/materials/grass.png")));
	std::unique_ptr<TerrainTexture> rTexture(new TerrainTexture(loader->loadTexture("res/materials/dirt.png")));
	std::unique_ptr<TerrainTexture> gTexture(new TerrainTexture(loader->loadTexture("res/materials/grassFlowers.png")));
	std::unique_ptr<TerrainTexture> bTexture(new TerrainTexture(loader->loadTexture("res/materials/path.png")));

	std::unique_ptr<TerrainTexture> blendMap(new TerrainTexture(loader->loadTexture("res/materials/blendMap.png")));

	//create ingame entity from assets
	std::unique_ptr<TexturedModel> texturedModel(new TexturedModel(model.get(), texture.get()));
	std::unique_ptr<TexturedModel> grassTexturedModel(new TexturedModel(grass.get(), grassTexture.get()));

	std::unique_ptr<Camera> camera(new Camera());
	std::unique_ptr<TerrainTexturePack> texturePack(new TerrainTexturePack(backgroundTexture.get(), rTexture.get(), gTexture.get(), bTexture.get()));
	std::unique_ptr<Terrain> terrain(new Terrain(0, 0, loader.get(), texturePack.get(), blendMap.get(), "res/materials/heightmap.png"));


	std::unique_ptr<Player> player(new Player(texturedModel.get(), glm::vec3(500, terrain->getHeightOfTerrain(500, 400), 400), glm::vec3(0, 0, 0), 1));
	std::unique_ptr<Entity> entity2(new Entity(texturedModel.get(), glm::vec3(500, terrain->getHeightOfTerrain(500, 395), 395), glm::vec3(0, 0, 0), 1));

	player->attachCameraToPlayer(camera.get());

	std::unique_ptr<Entity> entity(new Entity(texturedModel.get(), glm::vec3(500, terrain->getHeightOfTerrain(500, 500), 500), glm::vec3(0, 0, 0), 1));
	//std::unique_ptr<Entity> grassEntity(new Entity(grassTexturedModel.get(), glm::vec3(200, 0, 200), 0, 0, 0, 1));

	std::unique_ptr<Light> light(new Light(glm::vec3(20000, 40000, 20000), glm::vec3(1,1,1)));
	//registering random grass into a vector Entity
	std::vector<std::unique_ptr<Entity>> grassList;
	for(int i = 0; i < 10; i++)
	{
		float x = 510+i*(-3);
		float z = 510+i*2;
		float y = terrain->getHeightOfTerrain(x, z);
		grassList.push_back(std::unique_ptr<Entity> (new Entity(grassTexturedModel.get(), glm::vec3(x, y, z), glm::vec3(0, 0, 0), 1)));
	}

	while (true)
	{
		//Poll Events
		glfwPollEvents();

		//entity->increasePosition(0, 0, 0.2f);
		player->move(terrain.get());

		//std::cout << "x : " << player->getPosition().x << " y : " << player->getPosition().y << " z : " << player->getPosition().z << std::endl;

		//render stuff
		renderer->processTerrain(terrain.get());
		renderer->processEntity(entity.get());
		renderer->processEntity(entity2.get());
		for(int i = 0; i < grassList.size(); i++)
		{
			renderer->processEntity(grassList.at(i).get());
		}
		renderer->render(light.get(), camera.get());

		//update
		DisplayManager::updateDisplay();

		//close condition (thread breaker)
		if (glfwWindowShouldClose(DisplayManager::getDisplay()) || glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_ESCAPE)) { break; }
	}

	//exit stuff
	renderer->cleanUp();
	loader->cleanUp();
	DisplayManager::closeDisplay();
	glfwTerminate();
	return EXIT_SUCCESS;
}