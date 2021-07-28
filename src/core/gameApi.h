#pragma once
#include "../event/EventRegister.h"
#include "cbase_gamemode.h"

struct gameApi
{
    EventRegister* gameRegister;
    cbase_gamemode* gameMode;
};