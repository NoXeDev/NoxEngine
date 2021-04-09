#pragma once
#include <glfw3.h>
class DisplayManager
{
public:
	GLFWwindow* window = nullptr;
	int createDisplay();
	void updateDisplay();
	void closeDisplay();
	void showFPS();
	int getWidth();
	int getHeight();
private:
	const GLint WIDTH = 1920, HEIGHT = 1080;
	const char *NAME = "NoxEngine";
};

