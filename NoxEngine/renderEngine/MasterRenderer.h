#pragma once
#include "../shaders/StaticShader.h"
#include "Renderer.h"
#include "DisplayManager.h"
#include "../model/TexturedModel.h"
#include "../entities/Entity.h"
#include "../entities/Light.h"
#include "../entities/Camera.h"

#include <fstream>
#include <unordered_map>
#include <vector>

class MasterRenderer
{
private:
	StaticShader* shader = new StaticShader();
	Renderer* renderer;
	std::unordered_map<TexturedModel*, std::vector<Entity*>> entities;

public:
	MasterRenderer(DisplayManager *display);
	void render(Light *sun, Camera *camera);
	void cleanUp();
	void processEntity(Entity *entity);
};

