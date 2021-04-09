#pragma once

#include <glew.h>
#include <glm.hpp>
#include <fstream>
#include <unordered_map>
#include <vector>

#include "../model/TexturedModel.h"
#include "../entities/Entity.h"
#include "../shaders/StaticShader.h"
#include "../renderEngine/DisplayManager.h"

class Renderer
{
public:
	Renderer(DisplayManager* display, StaticShader* shader);
	void prepare();
	void render(std::unordered_map < TexturedModel*, std::vector<Entity*>> entities);
private:
	glm::mat4 projectionMatrix;
	void createProjectionMatrix(DisplayManager *display);
	StaticShader *shader;
	void prepareTexturedModel(TexturedModel* model);
	void unbindTexturedModel();
	void prepareInstance(Entity* entity);
};

