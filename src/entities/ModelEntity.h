#pragma once
#include "Entity.h"

class ModelEntity : public Entity{
    private:
        TexturedModel *model;
        float scale;
    public:
        ModelEntity(TexturedModel *model, glm::vec3 position, glm::vec3 rotation, float scale);

        TexturedModel* getModel();
        void setModel(TexturedModel *model);

        float getScale();
        void setScale(float scale);
};