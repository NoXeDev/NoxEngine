#include "DisplayManager.h"
#include <iostream>
#include <sstream>

#include "../common/const.h"

double lastTime;
int nbFrames;

const GLint WIDTH = 1920, HEIGHT = 1080;
GLFWwindow* window;

int DisplayManager::createDisplay()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(WIDTH, HEIGHT, GAME_NAME,
#if _DEBUG
		nullptr
#else
		glfwGetPrimaryMonitor()
#endif
		, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	

	if (window == nullptr) { return NOXENGINE_FATAL_WINDOW_CREATE; }

	glfwMakeContextCurrent(window);
	glViewport(0, 0, screenWidth, screenHeight);
	return 0;
}

GLFWwindow* DisplayManager::getDisplay()
{
	return window;
}

void DisplayManager::updateDisplay()
{
	glfwSwapBuffers(window);
}

void DisplayManager::closeDisplay()
{
	glfwDestroyWindow(window);
}

void DisplayManager::showFPS()
{
    // Measure speed
     double currentTime = glfwGetTime();
     double delta = currentTime - lastTime;
     nbFrames++;
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago

         double fps = double(nbFrames) / delta;

         std::stringstream ss;
         ss << GAME_NAME << " " << GAME_VERSION << " [" << fps << " FPS]";

         glfwSetWindowTitle(window, ss.str().c_str());

         nbFrames = 0;
         lastTime = currentTime;
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
