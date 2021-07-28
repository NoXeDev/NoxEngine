#pragma once
#include <iostream>
#include <ctime>

struct C_RES {
    bool res;
    const char* message;
};

typedef enum {
    LOGstdr,
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
        Cvar(const char* name, t* _ptr){
            this->name = name;
            this->_ptr = _ptr;
            
            /*C_RES res = */virtualConsole::template registerGlobalConVar<t>(this);
            /*if(res.res){
                ostringstream ss;
                ss << "Cvar registered : " << this->name;
                virtualConsole::log(ss.str().c_str());
            }else {
                ostringstream ss;
                ss << "Cvar register failed : " << this->name;
                virtualConsole::log(ss.str().c_str(), LOGerr);
            }*/
        }
        t* get(){
            return _ptr;
        }
        const char *name;
        t* _ptr;
};

template <class c, typename t>
class Cvar_c {
    public:
        Cvar_c(const char* name, t* _ptr, c* contextReference){
            this->name = name;
            this->_ptr = _ptr;
            
            /*C_RES res = */virtualConsole::template registerConVar<c, t>(this, contextReference);
            /*if(res.res){
                ostringstream ss;
                ss << "Cvar registered : " << this->name;
                virtualConsole::log(ss.str().c_str());
            }else {
                ostringstream ss;
                ss << "Cvar register failed : " << this->name;
                virtualConsole::log(ss.str().c_str(), LOGerr);
            }*/
        }
        t* get(){
            return _ptr;
        }
        const char *name;
        t* _ptr;
};