#pragma once
#include <string.h>
#include <iostream>
#include <typeinfo>
#include <vector>
#include "../common/types.h"

static std::vector<std::string> *logs;

class virtualConsole {
    public:
        static void init();
        static C_RES log(std::string value);
        static const char* getLastLine();
        static void free();
};