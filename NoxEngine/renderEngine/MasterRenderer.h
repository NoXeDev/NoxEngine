#pragma once
#include "../shaders/StaticShader.h"
#include "EntityRenderer.h"
#include "DisplayManager.h"
#include "../model/TexturedModel.h"
#include "../entities/Entity.h"
#include "../entities/Light.h"
#include "../entities/Camera.h"

#include <fstream>
#include <unordered_map>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class MasterRenderer
{
private:
	StaticShader* shader = new StaticShader();
	EntityRenderer* renderer;
	std::unordered_map<TexturedModel*, std::vector<Entity*>> entities;
	void createProjectionMatrix();
	glm::mat4 projectionMatrix;

public:
	MasterRenderer();
	void render(Light *sun, Camera *camera);
	void cleanUp();
	void processEntity(Entity *entity);
	void prepare();
};

