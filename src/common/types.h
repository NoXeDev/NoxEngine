#pragma once
#include <iostream>
#include <ctime>
#include "../renderEngine/MasterRenderer.h"
#include "../renderEngine/Loader.h"
#include "../guis/GuiRenderer.h"

typedef struct C_RES {
    bool res;
    const char* message;
};

typedef enum {
    LOGstdr,
    LOGwarn,
    LOGerr,
    LOGfatal
} logtype;

struct Clog {
    logtype type;
    tm* time;
    std::string message;
};

struct Cleaner {
    MasterRenderer *renderer;
    Loader *loader;
    GuiRenderer *gui;
};