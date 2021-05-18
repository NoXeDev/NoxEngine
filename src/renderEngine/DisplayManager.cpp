#include "DisplayManager.h"
#include <iostream>
#include <sstream>

#include "../common/const.h"
#include "../utils/Mouse.h"

double FPSlastTime;
int nbFrames;

const GLint WIDTH = 1920, HEIGHT = 1080;
GLFWwindow* window;

double lastFrameTime;
double delta;

int DisplayManager::createDisplay()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(WIDTH, HEIGHT, GAME_NAME, 
	#ifdef debug
	nullptr
	#else
	glfwGetPrimaryMonitor()
	#endif
	, nullptr);

	Mouse::Init(window);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	

	if (window == nullptr) { return NOXENGINE_FATAL_WINDOW_CREATE; }

	glfwMakeContextCurrent(window);
	glViewport(0, 0, screenWidth, screenHeight);
	lastFrameTime = getCurrentTime();
	return 0;
}

GLFWwindow* DisplayManager::getDisplay()
{
	return window;
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
	glfwDestroyWindow(window);
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