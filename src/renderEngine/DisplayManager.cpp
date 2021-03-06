#include "DisplayManager.h"
#include <iostream>
#include <sstream>

#include "../common/const.h"
#include "../utils/Mouse.h"
#include "../core/virtualConsole.h"
#include "../core/errorHandler.h"

double FPSlastTime;
int nbFrames;

GLFWwindow* window;

double lastFrameTime;
double delta;

void DisplayManager::createDisplay()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);

	// Cvar DisplayProperties
	Cvar<int> WIDTH("width", new int(vidMode->width)), HEIGHT("height", new int(vidMode->height));
	Cvar<bool> isFullScreen("fullscreen", new bool(true));
	/////////////////////////

	window = glfwCreateWindow(*WIDTH.get(), *HEIGHT.get(), GAME_NAME, 
	*isFullScreen.get() ? primaryMonitor : nullptr
	, nullptr);

	Mouse::Init(window);

	std::ostringstream ss;
	ss << "Screen resolution : " << *WIDTH.get() << " x " << *HEIGHT.get();
	virtualConsole::log(ss.str(), LOGdebug);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	

	if (window == nullptr) { errorHandler::fatal("Failed to create window"); }

	glfwMakeContextCurrent(window);
	glViewport(0, 0, screenWidth, screenHeight);

	//this clear color to black for avoid a white screen (it hurt) when Engine start
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	
	lastFrameTime = getCurrentTime();
}

GLFWwindow* DisplayManager::getDisplay()
{
	return window;
}

bool DisplayManager::displayShouldClose()
{
	return glfwWindowShouldClose(window);
}

void DisplayManager::updateDisplay()
{
	glfwSwapBuffers(window);
	double currentFrameTime = getCurrentTime();
	showFPS(currentFrameTime);
	delta = (currentFrameTime - lastFrameTime)/1000;
	lastFrameTime = currentFrameTime;
}

void DisplayManager::closeDisplay()
{
	if(window != nullptr){
		glfwDestroyWindow(window);
	}
}

void DisplayManager::showFPS(double currentTime)
{
    // Measure speed
	double FPSdelta = (currentTime/1000) - FPSlastTime;
     nbFrames++;
     if ( FPSdelta >= 1.0 ){ // If last cout was more than 1 sec ago

         double fps = double(nbFrames) / FPSdelta;

         std::stringstream ss;
         ss << GAME_NAME << " " << GAME_VERSION << " [" << fps << " FPS]";

         glfwSetWindowTitle(window, ss.str().c_str());

         nbFrames = 0;
         FPSlastTime = currentTime/1000;
     }
}

int DisplayManager::getWidth()
{
	int width;
	glfwGetWindowSize(window, &width, nullptr);
	return width;
}

int DisplayManager::getHeight()
{
	int height;
	glfwGetWindowSize(window, nullptr, &height);
	return height;
}

double DisplayManager::getCurrentTime()
{
	return glfwGetTime()*1000;
}

float DisplayManager::getFrameTimeSeconds()
{
	return delta;
}