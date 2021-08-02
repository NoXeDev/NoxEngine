#pragma once
#include <string.h>
#include <iostream>
#include <variant>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include "../common/types.h"
#include "errorHandler.h"

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
        static C_RES registerGlobalConVar(Cvar<t> *cvar)
        {
            if(cvars<t>.find(cvar->name) != cvars<t>.end())
            {
                // Cvar already exist
                C_RES res;
                res.res = false;
                res.retCode = 1;
                res.message = "Cvar already exist";
                return res;
            }
            else 
            {
                try{
                    cvars<t>.insert({cvar->name, cvar});
                }catch(...)
                {
                    C_RES res;
                    res.res = false;
                    res.retCode = 2;
                    res.message = "Error register cvar";
                    return res;
                }
            }
            C_RES res;
            res.res = true;
            return res;
        }

        template <typename r>
        static Cvar<r>* getCvar(const char *name)
        {
            if(cvars<r>.find(name) != cvars<r>.end())
            {
                // Cvar exist
                return cvars<r>.at(name);
            }
            else 
            {
                // Cvar doesn't exist
                return nullptr;
            }
        }
        static void free();
};