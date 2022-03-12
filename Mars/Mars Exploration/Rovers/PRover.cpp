#include "PRover.h"

int PRover::P_checkup = 0;
int PRover::P_count = 0;

PRover::PRover(int rspeed) :Rover(rspeed, POLAR)
{

}

bool PRover::endMaintenance(int currentDay)
{
	if (currentDay > checkup_first_Day + (P_checkup / 2))
		return true;
	return false;
}

int PRover::get_P_count()
{
	return P_count;
}
void PRover::set_P_count(int rP_count)
{
	P_count = rP_count > 0 ? rP_count : 0;
}
int PRover::get_P_checkup()
{
	return P_checkup;
}
void PRover::set_P_checkup(int rP_checkup)
{
	P_checkup = rP_checkup > 0 ? rP_checkup : 0;
}