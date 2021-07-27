#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include "../common/cbase.h"

class EventRegister {
    public:
        EventRegister();
        ~EventRegister();
        C_RES RegisteringEvent(const char *name);
        C_RES SubscribeEvent(const char* name, std::function<void()> callback);
        void fire(const char *name);

    private:
        std::unordered_map<const char*, std::vector<std::function<void()>>*> *events;
};