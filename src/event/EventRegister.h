#pragma once
#include "../common/types.h"
#include <unordered_map>
#include <functional>
#include <vector>

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