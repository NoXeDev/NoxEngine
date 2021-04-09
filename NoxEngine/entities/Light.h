#pragma once
#include <glm.hpp>
class Light
{
public:
	Light(glm::vec3 positions, glm::vec3 colour);
	glm::vec3 getPositions();
	void setPositsions(glm::vec3 positions);
	glm::vec3 getColour();
	void setColour(glm::vec3 colour);

private:
	glm::vec3 positions;
	glm::vec3 colour;
};

