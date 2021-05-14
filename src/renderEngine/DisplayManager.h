#pragma once
#include <glfw3.h>
class DisplayManager
{
public:
	static int createDisplay();
	static void updateDisplay();
	static void closeDisplay();
	static GLFWwindow* getDisplay();
	static void showFPS(double currentTime);
	static int getWidth();
	static int getHeight();
	static double getCurrentTime();
	static float getFrameTimeSeconds();
};

