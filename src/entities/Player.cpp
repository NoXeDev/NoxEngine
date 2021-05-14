#include "Player.h"
#include <iostream>

Player::Player(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, float scale): Entity(model, position, rotation, scale){}

void Player::move()
{
    this->checkInputs();
    this->increaseRotation(0, this->currentTurnSpeed * DisplayManager::getFrameTimeSeconds(), 0);
    float distance = this->currentSpeed * DisplayManager::getFrameTimeSeconds();
    float dx = (float) (distance * glm::sin(glm::radians(this->getRotation().y)));
    float dz = (float) (distance * glm::cos(glm::radians(this->getRotation().y)));
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

    if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_D)) {
		this->currentTurnSpeed = -this->TURN_SPEED;
	}else if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_A)) {
		this->currentTurnSpeed = this->TURN_SPEED;
	}else {
        this->currentTurnSpeed = 0;
    }

    if (glfwGetKey(DisplayManager::getDisplay(), GLFW_KEY_SPACE)) {
		this->jump();
	}
}