#include "Emergency_Mission.h"

int Emergency_Mission::E_Count = 0;

Emergency_Mission::Emergency_Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG)
	:Mission(fd, id, rTLOC, rMDUR, rSIG, EMERGENCY)
{
}


int Emergency_Mission::getE_Count()
{
	return E_Count;
}

void Emergency_Mission::inc_E_count()
{
	E_Count++;
}
