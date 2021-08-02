#pragma once
#include <iostream>
#include <sstream>
#include <ctime>

struct C_RES {
    bool res;
    int retCode;
    const char* message;
};

typedef enum {
    LOGstdr,
    LOGdebug,
    LOGwarn,
    LOGerr,
    LOGfatal
} logtype;

struct Clog {
    logtype type;
    tm* time;
    std::string message;
};

template <typename t>
class Cvar {
    public:
        Cvar(const char* name, t* _ptr = nullptr){
            this->name = name;
            this->_ptr = _ptr;

            // User specify Cvar who already exist
            if(_ptr == nullptr)
            {
                Cvar<t> *tmp = virtualConsole::template getCvar<t>(name);
                if(tmp == nullptr)
                {
                    // Cvar doesn't exist, so lets create it
                    std::ostringstream ss;
                    ss << name << " was asked before initialized, creating void ptr";
                    virtualConsole::log(ss.str(), LOGwarn);

                   *this->_ptr = *new t();
                }
                else
                {
                    // Construct this from cvar who already exist
                    *this->_ptr = *tmp->_ptr;
                }
            }
            else
            {
                // User have don't specify the Cvar exist but it exist. 
                // In this case, the existing Cvar will replace the current Cvar ptr

                C_RES res = virtualConsole::template registerGlobalConVar<t>(this);
                if(res.retCode == 1)
                {
                    Cvar<t> *tmp = virtualConsole::template getCvar<t>(name);
                    *this->_ptr = *tmp->_ptr;
                }
            }
        }
        t* get(){
            return _ptr;
        }
        const char *name;
        t* _ptr;
};