#include <iostream>
#ifndef _DEBUG
#include <Windows.h>
#endif

#include <glew.h>
#include <glfw3.h>
#include <chrono>
#include <memory>

#include "common/cbase.h"
#include "game/cmain.h"

static API EngineCleaner;
void globalCleanUp();
void engineTick();
bool engineThreadBreaker();

#ifndef _DEBUG
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){
#else
int main(){
#endif
	//Init the Virtual console and error handler for Handle errors
	virtualConsole::init();
	errorHandler::init(&EngineCleaner);
	//Init GLFW 
	if (!glfwInit()) { errorHandler::fatal("[ERROR] - Initialise GLFW failed"); }

	//Window creation
	DisplayManager::createDisplay();

	//Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { errorHandler::fatal("[ERROR] - Initialise GLEW failed"); }

	//create loading stuff and registering into API
	std::unique_ptr<Loader> loader(new Loader());
	EngineCleaner.loader = loader.get();
	std::unique_ptr<MasterRenderer> renderer(new MasterRenderer());
	EngineCleaner.renderer = renderer.get();
	std::unique_ptr<GuiRenderer> guiRenderer(new GuiRenderer(loader.get()));
	EngineCleaner.gui = guiRenderer.get();
	EngineCleaner.engineTickCallback = engineTick;
	EngineCleaner.engineThreadBreaker = engineThreadBreaker;

	//create global Cvar here
	int sv_test = 1;
	Cvar<int> cvar_test("sv_test", &sv_test);

	//print Cvar and create ptr of him
	virtualConsole::log(std::to_string(*cvar_test.get()).c_str());
	int *alsoSv_test = virtualConsole::getCvar<int>("sv_test")->get();

	//edit cvar value by ptr
	*alsoSv_test = 9;

	//printing the new value
	virtualConsole::log(std::to_string(*cvar_test.get()).c_str());

	cmain(&EngineCleaner);

	//errorHandler::fatal("Testing fatal error");

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