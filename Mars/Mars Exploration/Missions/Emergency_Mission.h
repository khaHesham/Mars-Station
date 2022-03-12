#pragma once
#include "Mission.h"

class Emergency_Mission :public Mission
{
    static int E_Count;
public:
    Emergency_Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG);
    
    static int getE_Count();
    static void inc_E_count();
};

