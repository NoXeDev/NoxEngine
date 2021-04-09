#include "DisplayManager.h"
#include <iostream>
#include <sstream>

#include "../common/const.h"

double lastTime;
int nbFrames;

int DisplayManager::createDisplay()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	this->window = glfwCreateWindow(this->WIDTH, this->HEIGHT, this->NAME, 
#if _DEBUG
		nullptr
#else
		glfwGetPrimaryMonitor()
#endif
		, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(this->window, &screenWidth, &screenHeight);
	

	if (this->window == nullptr) { return NOXENGINE_FATAL_WINDOW_CREATE; }

	glfwMakeContextCurrent(this->window);
	glViewport(0, 0, screenWidth, screenHeight);
	return 0;
}

void DisplayManager::updateDisplay()
{
	glfwSwapBuffers(this->window);
}

void DisplayManager::closeDisplay()
{
	glfwDestroyWindow(this->window);
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

         glfwSetWindowTitle(this->window, ss.str().c_str());

         nbFrames = 0;
         lastTime = currentTime;
     }
}

int DisplayManager::getWidth()
{
	int width;
	glfwGetWindowSize(this->window, &width, nullptr);
	return width;
}

int DisplayManager::getHeight()
{
	int height;
	glfwGetWindowSize(this->window, nullptr, &height);
	return height;
}
