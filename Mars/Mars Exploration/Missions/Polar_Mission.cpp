#include "Polar_Mission.h"

int Polar_Mission::P_Count = 0;

Polar_Mission::Polar_Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG)
	:Mission(fd, id, rTLOC, rMDUR, rSIG, POLAR)
{

}

int Polar_Mission::getP_Count()
{
	return P_Count;
}

void Polar_Mission::inc_P_Count()
{
	P_Count++;
}
