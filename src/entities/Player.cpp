#include "Player.h"
#include "Camera.h"
#include <iostream>

Player::Player(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, float scale): Entity(model, position, rotation, scale){}

void Player::move()
{
    if(this->hasCamera || this->camera != nullptr){
        this->checkInputs();
        this->camera->move(this->getPosition());
        //std::cout << this->getRotation().y;
        this->rotation.y = - this->camera->getRotation().y;
        float distance = this->currentSpeed * DisplayManager::getFrameTimeSeconds();
        float dx = (float) (distance * glm::sin(glm::radians(this->camera->getRotation().y + this->DIRECTION_VECTOR)));
        float dz = (float) (distance * -glm::cos(glm::radians(this->camera->getRotation().y + this->DIRECTION_VECTOR)));
        this->increasePosition(dx, 0, dz);

        this->upwardsSpeed += this->GRAVITY * DisplayManager::getFrameTimeSeconds();
        this->increasePosition(0, upwardsSpeed * DisplayManager::getFrameTimeSeconds(), 0);
        if(this->getPosition().y < this->TERRAIN_HEIGHT)
        {
            this->upwardsSpeed = 0;
            this->isInAir = false;
            this->getPositionPTR()->y = TERRAIN_HEIGHT;
        }
    }
}

void Player::jump()
{
    if(!isInAir){
        this->upwardsSpeed = JUMP_POWER;
        this->isInAir = true;
    }
}

void Player::checkInputs()
{
    if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_W)) {
		this->currentSpeed = this->RUN_SPEED;
	}else if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_S)) {
		this->currentSpeed = -this->RUN_SPEED;
	}else {
        this->currentSpeed = 0;
    }

    if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_LEFT_SHIFT)){
        this->currentSpeed += 30.0f;
    }

    if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_D)) {
		this->DIRECTION_VECTOR = 90.0f;
	}else if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_A)) {
		this->DIRECTION_VECTOR = -90.0f;
	}else {
        this->DIRECTION_VECTOR = 0;
    }

    if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_SPACE)) {
		this->jump();
	}
}

void Player::attachCameraToPlayer(Camera* camera)
{
    this->camera = camera;
    this->hasCamera = true;
}