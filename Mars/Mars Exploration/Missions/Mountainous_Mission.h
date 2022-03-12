#pragma once
#include "Mission.h"
class Mountainous_Mission : public Mission
{
    static int M_Count;
    static int AutoP;
public:
    Mountainous_Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG);
    static int getM_Count();
    static void inc_M_COunt();
    static void dec_M_COunt();
   
    static void setAutoP(int AP);
    static int getAutoP();
};

