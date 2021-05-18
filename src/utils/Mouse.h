#pragma once
#include <glfw3.h>
#include <glm.hpp>

class Mouse {
    public:
        static void Init(GLFWwindow* window);
        static bool isHoverd();

        static void setCursorPositions(glm::vec2 positions);
        static glm::vec2 getCursorPositions();
};