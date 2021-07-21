#pragma once
#include <string.h>
#include <iostream>
#include <typeinfo>
#include <vector>
#include "../common/types.h"

static std::vector<Clog> *logs;

class virtualConsole {
    public:
        static void init();
        static void log(std::string value);
        static Clog getLastLog();
        static void free();
};