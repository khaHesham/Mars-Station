#include "Rover.h"

int Rover::N = 0;
int Rover::rover_count = 0;
int Rover::counter = 0;

Rover::Rover(int rspeed, TYPE rtype)
{
	type = rtype;
	ID = counter++;
	ROVER_LOCATION = WAITING_ROVERS;
	mission_count = 0;
	speed = rspeed;
	checkup_first_Day = 0;

	coveredDistance = 0;
	nextChkCoveredDist = 1000;
}
void Rover::increment_missions()
{
	mission_count++;
}
TYPE Rover::getType()const
{
	return type;
}
int Rover::getSpeed()const
{
	return speed;
}


bool Rover::needsCheckup()const
{
	return (mission_count % N == 0 && mission_count);
}

int Rover::GetID()
{
	return ID;
}

void Rover::set_Rover_Location(int loc)
{
	ROVER_LOCATION = loc;
}

void Rover::set_checkup_first_Day(int cD)
{
	checkup_first_Day = cD;
}

void Rover::set_CD(int cd)
{
	CD = cd;
}


int Rover::get_rover_count()
{
	return rover_count;
}
void Rover::set_rover_count(int rrover_count)
{
	rover_count = rrover_count > 0 ? rrover_count : 0;
}
int Rover::get_N()
{
	return N;
}
void Rover::set_N(int rN)
{
	N = rN > 0 ? rN : 0;
}

void Rover::incCoveredDist(int dist)
{
	dist > 0 ? coveredDistance += dist : coveredDistance = coveredDistance;
}

bool Rover::NeedsMaintenance()
{
	if (coveredDistance > nextChkCoveredDist) // every 10K we need to do a maintenance
	{
		nextChkCoveredDist += nextChkCoveredDist;
		return true;
	}
	return false;
}

float Rover::getCoveredDist()
{
	return coveredDistance;
}

void Rover::setSpeed(int s)
{
	s > 0 ? speed = s : speed = speed;
}


int Rover::get_checkup_first_Day()
{
	return checkup_first_Day;
}

float Rover::Priority()
{
	if (ROVER_LOCATION == WAITING_ROVERS)
		return speed;
	else if (ROVER_LOCATION == IN_EXECUTION_ROVERS)
		return(1.0 / CD);
}