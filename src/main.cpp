#include <iostream>
#include <Windows.h>
#include <glew.h>
#include <glfw3.h>
#include <chrono>
#include <memory>

#include "common/cbase.h"
#include "common/engineApi.h"
#include "game/cmain.h"

static API EngineCleaner;
void globalCleanUp();
void engineTick();
bool engineThreadBreaker();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){
	// Init the Virtual console and error handler for Handle errors
	virtualConsole::init();
	errorHandler::init(&EngineCleaner);
	// Init GLFW 
	if (!glfwInit()) { errorHandler::fatal("[ERROR] - Initialise GLFW failed"); }

	// Testing Cvar priority
	Cvar<bool>("fullscreen", new bool(false));

	// Window creation
	DisplayManager::createDisplay();

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { errorHandler::fatal("[ERROR] - Initialise GLEW failed"); }

	// create loading stuff and registering into API
	std::unique_ptr<Loader> loader(new Loader());
	EngineCleaner.loader = loader.get();
	std::unique_ptr<MasterRenderer> renderer(new MasterRenderer(loader.get()));
	EngineCleaner.renderer = renderer.get();
	std::unique_ptr<GuiRenderer> guiRenderer(new GuiRenderer(loader.get()));
	EngineCleaner.gui = guiRenderer.get();
	EngineCleaner.engineTickCallback = engineTick;
	EngineCleaner.engineThreadBreaker = engineThreadBreaker;
	////////////////////////////////////////////////

	// Main Game
	cmain(&EngineCleaner);

	//exit stuff
	globalCleanUp();
	return EXIT_SUCCESS;
}

void engineTick(){
	glfwPollEvents();
}

bool engineThreadBreaker()
{
	return glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_ESCAPE);
}

void globalCleanUp()
{
	EngineCleaner.renderer->cleanUp();
	EngineCleaner.loader->cleanUp();
	EngineCleaner.gui->cleanUp();
	DisplayManager::closeDisplay();
	virtualConsole::free();
	glfwTerminate();
}