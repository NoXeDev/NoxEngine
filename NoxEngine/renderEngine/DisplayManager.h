#pragma once
#include <glfw3.h>
class DisplayManager
{
public:
	static int createDisplay();
	static void updateDisplay();
	static void closeDisplay();
	static GLFWwindow* getDisplay();
	static void showFPS();
	static int getWidth();
	static int getHeight();
};

