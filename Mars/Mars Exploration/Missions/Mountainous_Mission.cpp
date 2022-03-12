#include "Mountainous_Mission.h"

int Mountainous_Mission::AutoP = 0;
int Mountainous_Mission::M_Count = 0;

Mountainous_Mission::Mountainous_Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG)
    :Mission(fd, id, rTLOC, rMDUR, rSIG, MOUNTAINOUS)
{
}

int Mountainous_Mission::getM_Count()
{
    return M_Count;
}

void Mountainous_Mission::inc_M_COunt()
{
    M_Count++;
}

void Mountainous_Mission::dec_M_COunt()
{
    M_Count--;
}


void Mountainous_Mission::setAutoP(int AP)
{
    AutoP = AP;
}

int Mountainous_Mission::getAutoP()
{
    return AutoP;
}