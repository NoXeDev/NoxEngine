#pragma once
#include <iostream>
#include <ctime>

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