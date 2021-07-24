#pragma once
#include <string.h>
#include <iostream>
#include <variant>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include "../common/types.h"

static std::vector<Clog> *logs;

template <typename c>
static std::unordered_map<const char*, Cvar<c>*> cvars;

class virtualConsole {
    public:
        static std::vector<Clog> *getLogs();
        static void init();
        static void log(std::string value, logtype type = LOGstdr);
        static Clog getLastLog();

        template <typename t>
        static C_RES registerConVar(Cvar<t> *cvar)
        {
            try{
                cvars<t>.insert({cvar->name, cvar});
            }catch(...)
            {
                C_RES res;
                res.res = false;
                res.message = "Error register cvar";
                return res;
            }
            C_RES res;
            res.res = true;
            return res;
        }

        template <typename r>
        static Cvar<r>* getCvar(const char *name)
        {
            return cvars<r>.at(name);
        }
        static void free();
};