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

template <class c, typename t>
static std::unordered_map<c*, std::unordered_map<const char*, Cvar_c<c, t>*>> cvarsTable;

class virtualConsole {
    public:
        static std::vector<Clog> *getLogs();
        static void init();
        static void log(std::string value, logtype type = LOGstdr);
        static Clog getLastLog();

        template <typename t>
        static C_RES registerGlobalConVar(Cvar<t> *cvar)
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

        template <class c, typename t>
        static C_RES registerConVar(Cvar_c<c, t> *cvar, c *classContext)
        {
            try{
                if(this->cvarsTable.find(classContext) != this->cvarsTable.end()){
                    this->cvarsTable.at(classContext).insert({cvar->name, cvar});
                }else {
                    this->cvarsTable.insert({classContext, std::unordered_map<const char*, Cvar_c<c, t>*>{cvar->name, cvar}});
                }
            }catch(...){
                C_RES failedRes;
                failedRes.res = false;
                failedRes.message = "Error registering cvarTable for the specified class";
                return failedRes;
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
        template <class c, typename t>
        static Cvar_c<c, t>* getCvar(const char *name, c *classContext)
        {
            return cvarsTable<c, t>.at(classContext).at(name);
        }
        static void free();
};