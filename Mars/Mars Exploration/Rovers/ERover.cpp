#include "ERover.h"

int ERover::E_checkup = 0;
int ERover::E_count = 0;

ERover::ERover(int rspeed) :Rover(rspeed, EMERGENCY)
{

}

bool ERover::endMaintenance(int currentDay)
{
	if (currentDay > checkup_first_Day + (E_checkup / 2))
		return true;
	return false;
}

int ERover::get_E_count()
{
	return E_count;
}
void ERover::set_E_count(int rE_count)
{
	E_count = rE_count > 0 ? rE_count : 0;
}
int ERover::get_E_checkup()
{
	return E_checkup;
}
void ERover::set_E_checkup(int rE_checkup)
{
	E_checkup = rE_checkup > 0 ? rE_checkup : 0;
}