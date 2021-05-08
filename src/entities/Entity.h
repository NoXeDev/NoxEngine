#pragma once
#include "../model/TexturedModel.h"
#include <glm.hpp>
class Entity
{
private:
	TexturedModel* model;
	glm::vec3 position;
	float rotX, rotY, rotZ;
	float scale;

public:
	Entity(TexturedModel* model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);

	//getters and setters

	TexturedModel* getModel();
	void setModel(TexturedModel* model);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	float getRotX();
	void setRotX(float rotX);
	float getRotY();
	void setRotY(float rotY);
	float getRotZ();
	void setRotZ(float rotZ);
	float getScale();
	void setScale(float scale);

	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);
};

