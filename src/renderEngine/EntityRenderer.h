#pragma once

#include <glew.h>
#include <glm.hpp>
#include <fstream>
#include <unordered_map>
#include <vector>

#include "../model/TexturedModel.h"
#include "../entities/ModelEntity.h"
#include "../shaders/StaticShader.h"
#include "../renderEngine/DisplayManager.h"

class EntityRenderer
{
public:
	EntityRenderer(StaticShader* shader, glm::mat4 projectionMatrix);
	void render(std::unordered_map < TexturedModel*, std::vector<ModelEntity*>> entities);
private:
	StaticShader *shader;
	void prepareTexturedModel(TexturedModel* model);
	void unbindTexturedModel();
	void prepareInstance(ModelEntity* entity);
};

