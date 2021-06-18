#pragma once
#include "Entity.h"
#include <glfw3.h>
#include "Camera.h"
#include "../terrain/Terrain.h"
#include "../renderEngine/DisplayManager.h"
#include <glm.hpp>

class Player:public Entity{
    private:
        const float RUN_SPEED = 20;
        const float GRAVITY = -50;
        const float JUMP_POWER = 30;
        const float TERRAIN_HEIGHT = 0;

        float DIRECTION_VECTOR = 0;

        float currentSpeed = 0;
        float upwardsSpeed = 0;

        bool isInAir = false;

        Camera* camera = nullptr;
        bool hasCamera = false;

        void jump();

    public:
        Player(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, float scale);
        void move(Terrain *terrain);
        void checkInputs();

        void attachCameraToPlayer(Camera* camera);
};