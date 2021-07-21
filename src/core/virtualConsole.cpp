#include "virtualConsole.h"

void virtualConsole::init()
{
    logs = new std::vector<std::string>{};
}

C_RES virtualConsole::log(std::string value)
{
    logs->push_back(value);
    std::cout << value.c_str() << std::endl;
    C_RES res;
    res.res = true;
    return res;
}

const char* virtualConsole::getLastLine()
{
    return logs->at(logs->size() - 1).c_str();
}

void virtualConsole::free()
{
    delete logs;
}