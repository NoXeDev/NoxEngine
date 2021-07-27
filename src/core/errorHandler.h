#pragma once
#include <Windows.h>
#include <iostream>
#include "virtualConsole.h"
#include "../common/types.h"



static API *errCleaner;

class errorHandler {
    public:
        static void init(API *cleaner);
        static void fatal(std::string err);
        static void writelogs();
        static void stdrErr(std::string err);
};