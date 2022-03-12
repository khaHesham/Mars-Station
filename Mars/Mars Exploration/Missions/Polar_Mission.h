#pragma once
#include "Mission.h"
class Polar_Mission : public Mission
{
    static int P_Count;

public:
    Polar_Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG);
    static int getP_Count();
    static void inc_P_Count();
};

