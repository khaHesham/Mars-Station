#include "MRover.h"

int MRover::M_checkup = 0;
int MRover::M_count = 0;

MRover::MRover(int rspeed):Rover(rspeed, MOUNTAINOUS)
{

}

bool MRover::endMaintenance(int currentDay)
{
	if (currentDay > checkup_first_Day + (M_checkup / 2))
		return true;
	return false;
}

int MRover::get_M_count()
{
	return M_count;
}
void MRover::set_M_count(int rM_count)
{
	M_count = rM_count > 0 ? rM_count : 0;
}
int MRover::get_M_checkup()
{
	return M_checkup;
}
void MRover::set_M_checkup(int rM_checkup)
{
	M_checkup = rM_checkup > 0 ? rM_checkup: 0;
}