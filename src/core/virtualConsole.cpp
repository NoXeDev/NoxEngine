#include "virtualConsole.h"

void virtualConsole::init()
{
    logs = new std::vector<Clog>{};
}

void virtualConsole::log(std::string value, logtype type)
{
    Clog currentLog;
    currentLog.message = value;
    currentLog.type = type;

    time_t now = time(0);
    currentLog.time = localtime(&now);

    logs->push_back(currentLog);
#ifdef _DEBUG
    std::cout << "[" << currentLog.time->tm_hour << ":" << currentLog.time->tm_min  << 
    ":" << currentLog.time->tm_sec << "] - " << currentLog.message.c_str() << std::endl;
#endif

    if(type == LOGfatal)
    {
        errorHandler::fatal(value);
    }
}

Clog virtualConsole::getLastLog()
{
    return logs->at(logs->size() - 1);
}

void virtualConsole::free()
{
    if(logs != nullptr){
        delete logs;
    }
}

std::vector<Clog> *virtualConsole::getLogs()
{
    return logs;
}