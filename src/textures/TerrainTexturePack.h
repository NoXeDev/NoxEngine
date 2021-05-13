#pragma once
#include "TerrainTexture.h"

class TerrainTexturePack {
    private:
        TerrainTexture *backgroundTexture;
        TerrainTexture *rTexture;
        TerrainTexture *gTexture;
        TerrainTexture *bTexture;
    
    public:
        TerrainTexturePack(TerrainTexture *backgroundTexture, TerrainTexture *rTexture, TerrainTexture *gTexture, TerrainTexture *bTexture){
            this->backgroundTexture = backgroundTexture;
            this->rTexture = rTexture;
            this->gTexture = gTexture;
            this->bTexture = bTexture;
        };

        TerrainTexture *getBackgroundTexture(){
            return this->backgroundTexture;
        }

        TerrainTexture *getRTexture(){
            return this->rTexture;
        }

        TerrainTexture *getGTexture(){
            return this->gTexture;
        }

        TerrainTexture *getBTexture(){
            return this->bTexture;
        }

};