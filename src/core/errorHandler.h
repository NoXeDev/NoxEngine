#pragma once
#include <Windows.h>
#include <iostream>
#include "virtualConsole.h"
#include "../common/types.h"



static Cleaner *errCleaner;

class errorHandler {
    public:
        static void init(Cleaner *cleaner);
        static void fatal(std::string err);
        static void writelogs();
        static void stdrErr(std::string err);
};