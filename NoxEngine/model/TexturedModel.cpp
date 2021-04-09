#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel *model, ModelTexture *texture): rawModel(*model), texture(*texture)
{
}

RawModel TexturedModel::getRawModel()
{
	return this->rawModel;
}

ModelTexture TexturedModel::getTexture()
{
	return this->texture;
}
