#pragma once
#include <string.h>
#include <iostream>
#include <typeinfo>
#include <vector>
#include "../common/types.h"

static std::vector<Clog> *logs;

class virtualConsole {
    public:
        static std::vector<Clog> *getLogs();
        static void init();
        static void log(std::string value, logtype type = LOGstdr);
        static Clog getLastLog();
        static void free();
};