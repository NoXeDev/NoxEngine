#include "Mouse.h"
#include <iostream>

GLFWwindow* window_ptr;

//make static class because we want only one mouse cursor

void Mouse::Init(GLFWwindow* window)
{
    window_ptr = window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    setCursorPositions(glm::vec2(0,0));
}

bool Mouse::isHoverd()
{
    return glfwGetWindowAttrib(window_ptr, GLFW_HOVERED);
}

void Mouse::setCursorPositions(glm::vec2 positions)
{
    glfwSetCursorPos(window_ptr, positions.x, positions.y);
}

glm::vec2 Mouse::getCursorPositions()
{
    double xpos, ypos;
    glfwGetCursorPos(window_ptr, &xpos, &ypos); 
    return glm::vec2(xpos, ypos);
}