#pragma once
#include <glew.h>
#include <glfw3.h>
class DisplayManager
{
public:
	static void createDisplay();
	static void updateDisplay();
	static void closeDisplay();
	static bool displayShouldClose();
	static GLFWwindow* getDisplay();
	static void showFPS(double currentTime);
	static int getWidth();
	static int getHeight();
	static double getCurrentTime();
	static float getFrameTimeSeconds();
};

