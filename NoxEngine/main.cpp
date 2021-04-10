#include <iostream>
#include <Windows.h>


#include <glew.h>
#include <glfw3.h>
#include <array>
#include <fstream>
#include <chrono>

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

float readfloat(FILE* f) {
	float v;
	fread((void*)(&v), sizeof(v), 1, f);
	return v;
}

int fatalError(const char* message) {
	std::cout << message << std::endl;
	glfwTerminate();

	return EXIT_FAILURE;
}

#if not _DEBUG
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
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
	std::unique_ptr<RawModel> model(NMloader::loadNMmodel("res/dragon.nm", loader.get()));
	std::unique_ptr<ModelTexture> texture(new ModelTexture(loader->loadTexture("res/stallTexture.png")));
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Loading time : " << (float)duration.count() / 1000000 << "'s" << std::endl;

	//set textures varaibles
	texture->setShineDamper(10);
	texture->setReflectivity(1);	

	//create ingame entity from assets
	std::unique_ptr<TexturedModel> texturedModel(new TexturedModel(model.get(), texture.get()));
	std::unique_ptr<Entity> entity(new Entity(texturedModel.get(), glm::vec3(0, -5, -20), 0, 0, 0, 1));
	std::unique_ptr<Light> light(new Light(glm::vec3(0, 0, 1), glm::vec3(1,1,1)));
	std::unique_ptr<Camera> camera(new Camera());

	while (true)
	{
		//Poll Events
		glfwPollEvents();

		//entity->increaseRotation(0, 1, 0);
		camera->move();

		//render stuff
		renderer->processEntity(entity.get());
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