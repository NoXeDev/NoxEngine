#pragma once
#include "../model/TexturedModel.h"
#include <glm.hpp>
class Entity
{
private:
	TexturedModel* model;
	glm::vec3 position;
	glm::vec3 rotation;
	float scale;

public:
	Entity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, float scale);

	//getters and setters
	glm::vec3* getPositionPTR();
	TexturedModel* getModel();
	void setModel(TexturedModel* model);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getRotation();
	void setRotation(glm::vec3 rotation);
	float getScale();
	void setScale(float scale);

	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);
};

