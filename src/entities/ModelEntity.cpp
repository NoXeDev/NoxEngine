#include "ModelEntity.h"

ModelEntity::ModelEntity(WorldApi *worldApi, TexturedModel *model, glm::vec3 position, glm::vec3 rotation, float scale)
:Entity(worldApi, position, rotation)
{
    this->model = model;
    this->scale = scale;
}

TexturedModel* ModelEntity::getModel()
{
    return this->model;
}

void ModelEntity::setModel(TexturedModel *model)
{
    this->model = model;
}

float ModelEntity::getScale()
{
    return this->scale;
}

void ModelEntity::setScale(float scale)
{
    this->scale = scale;
}