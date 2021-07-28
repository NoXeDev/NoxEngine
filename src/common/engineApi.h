#pragma once
#include "../renderEngine/MasterRenderer.h"
#include "../renderEngine/Loader.h"
#include "../guis/GuiRenderer.h"

struct API {
    MasterRenderer *renderer;
    Loader *loader;
    GuiRenderer *gui;
    void(*engineTickCallback)();
    bool(*engineThreadBreaker)();
};