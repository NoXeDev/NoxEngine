#include "EventRegister.h"

EventRegister::EventRegister()
{
    this->events = new std::unordered_map<const char*, std::vector<std::function<void()>>*>();
}

EventRegister::~EventRegister()
{
    delete events;
}

C_RES EventRegister::RegisteringEvent(const char *name){
    if(this->events->find(name) != this->events->end()){
        C_RES res;
        res.res = false;
        res.message = "Event already exist";
        return res;
    }else {
        this->events->insert({name, new std::vector<std::function<void()>>{}});
        C_RES res;
        res.res = true;
        return res;
    }
}

C_RES EventRegister::SubscribeEvent(const char *name, std::function<void()> callback)
{
    if(this->events->find(name) != this->events->end()){
        this->events->at(name)->push_back(callback);
        C_RES res;
        res.res = true;
        return res;
    }else {
        C_RES res;
        res.res = false;
        res.message = "No Event named "+*name;
        return res;
    }
}

void EventRegister::fire(const char *name){
    for(std::function<void()> function : *this->events->at(name)){
        function();
    }
}