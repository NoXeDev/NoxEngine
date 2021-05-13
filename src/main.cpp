#include <iostream>

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

int fatalError(const char* message) {
	std::cout << message << std::endl;
	glfwTerminate();

	return EXIT_FAILURE;
}

int main(){
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
	std::unique_ptr<RawModel> model(NMloader::loadNMmodel("res/models/dragon.nm", loader.get()).at(0));
	std::unique_ptr<RawModel> grass(NMloader::loadNMmodel("res/models/grass.nm", loader.get()).at(0));
	std::unique_ptr<RawModel> squareModel(NMloader::loadNMmodel("res/models/square.nm", loader.get()).at(0));
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

	//create ingame entity from assets
	std::unique_ptr<TexturedModel> texturedModel(new TexturedModel(model.get(), texture.get()));
	std::unique_ptr<TexturedModel> grassTexturedModel(new TexturedModel(grass.get(), grassTexture.get()));
	std::unique_ptr<TexturedModel> squareTextured(new TexturedModel(squareModel.get(), texture.get()));

	std::unique_ptr<Entity> entity(new Entity(texturedModel.get(), glm::vec3(500, 0, 500), 0, 0, 0, 1));
	std::unique_ptr<Entity> square(new Entity(squareTextured.get(), glm::vec3(510, 5, 510), 0, 0, 0, 1));
	//std::unique_ptr<Entity> grassEntity(new Entity(grassTexturedModel.get(), glm::vec3(200, 0, 200), 0, 0, 0, 1));

	std::unique_ptr<Light> light(new Light(glm::vec3(2000, 2000, 2000), glm::vec3(1,1,1)));
	std::unique_ptr<Camera> camera(new Camera(glm::vec3(500, 8, 550)));

	std::unique_ptr<Terrain> terrain(new Terrain(0, 0, loader.get(), new ModelTexture(loader->loadTexture("res/materials/grass.png"))));
	std::unique_ptr<Terrain> terrain2(new Terrain(1, 0, loader.get(), new ModelTexture(loader->loadTexture("res/materials/grass.png"))));

	//registering random grass into a vector Entity
	std::vector<std::unique_ptr<Entity>> grassList;
	for(int i = 0; i < 10; i++)
	{
		grassList.push_back(std::unique_ptr<Entity> (new Entity(grassTexturedModel.get(), glm::vec3(510+i*(-3), 0, 510+i*2), 0, 0, 0, 1)));
	}

	while (true)
	{
		//Poll Events
		glfwPollEvents();

		//entity->increasePosition(0.2f, 0, 0);
		camera->move();

		std::cout << "x : " << camera->getPosition().x << " y : " << camera->getPosition().y << " z : " << camera->getPosition().z << std::endl;

		//render stuff
		renderer->processTerrain(terrain.get());
		renderer->processTerrain(terrain2.get());
		renderer->processEntity(entity.get());
		renderer->processEntity(square.get());
		for(int i = 0; i < grassList.size(); i++)
		{
			renderer->processEntity(grassList.at(i).get());
		}
		renderer->render(light.get(), camera.get());

		//update
		DisplayManager::updateDisplay();
		DisplayManager::showFPS();

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