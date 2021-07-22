#include "errorHandler.h"
#include <direct.h>
#include <locale>

std::vector<std::string> charTypesLogs = {
    "",
    "WARN",
    "ERROR",
    "FATAL"
};

void errorHandler::fatal(std::string err)
{
    virtualConsole::log(err, LOGfatal);
    if(errCleaner->renderer != nullptr)
    {
        errCleaner->renderer->cleanUp();
    }
    if(errCleaner->loader != nullptr)
    {
        errCleaner->loader->cleanUp();
    }
    if(errCleaner->gui != nullptr)
    {
        errCleaner->gui->cleanUp();
    }
    DisplayManager::closeDisplay();

    MessageBox(NULL, std::wstring(err.begin(), err.end()).c_str(), L"NoxEngine fatal", MB_OK|MB_ICONERROR);
    errorHandler::writelogs();
    virtualConsole::free();
    glfwTerminate();
    exit(1);
}


void errorHandler::init(Cleaner *cleaner)
{
    errCleaner = cleaner;
}

void errorHandler::writelogs()
{
    _mkdir("./crashlogs");
    time_t now = time(0);
    tm *time = localtime(&now);
    ostringstream path;
    path << "./crashlogs/" << time->tm_mday << "-" << time->tm_mon << "-" << (time->tm_year + 1900)
    << "#" << time->tm_hour << "." << time->tm_min << "." << time->tm_sec << "--crashlogs.txt";
    ofstream fs;
    fs.open(path.str());
    if (!fs) {
        std::cout << "Unable to open file";
        exit(1);
    }
    for(Clog batch : *virtualConsole::getLogs())
    {
        ostringstream ss;
        ss << "[" << batch.time->tm_hour << ":" << batch.time->tm_min  << 
        ":" << batch.time->tm_sec << "] - " << charTypesLogs.at(batch.type).c_str()
        << " : " << batch.message.c_str() << "\n";
        fs << ss.str().c_str();
    }
    fs.close();
}