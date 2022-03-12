#include "Mission.h"

int Mission::Missions_Count = 0;


Mission::Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG, TYPE rtype, Rover* rrover)
{
	type = rtype;
	setformulation(fd);
	setID(id);
	setTarget(rTLOC);
	setDuration(rMDUR);
	setSignificance(rSIG);
	rover = nullptr;
	Location_List = WAITING_LIST;
}


void Mission::setTarget(int rTLOC)
{
	if (rTLOC > 0)
		TLOC = rTLOC;
	else rTLOC = 0;
}

void Mission::setDuration(int rMDUR)
{
	if (rMDUR > 0)
		MDUR = rMDUR;
	else MDUR = 0;
}

void Mission::setSignificance(int rSIG)
{
	if (rSIG > 0)
		SIG = rSIG;
	else
		SIG = 0;
}

void Mission::setID(int id)
{
	if (id > 0)
		ID = id;
	else
		ID = 0;
}

void Mission::setformulation(int fd)
{
	FD = fd;
}

void Mission::setM_location(int loc)
{
	Location_List = loc;
}

int Mission::getFormulation()
{
	return FD;
}

int Mission::getWaiting()
{
	return WD;
}

int Mission::getexectution()
{
	return ED;
}

int Mission::getLocation()
{
	return TLOC;
}

int Mission::getDuration()
{
	return MDUR;
}

int Mission::getSignificance()
{
	return SIG;
}

int Mission::getCount()
{
	return Missions_Count;
}

int Mission::getID()
{
	return ID;
}

int Mission::getCompletion()
{
	return CD;
}

int Mission::getM_location()
{
	return Location_List;
}

TYPE Mission::getType()
{
	return type;
}


void Mission::AssignRover(Rover* rrover)
{
	rover = rrover;
	rover->set_CD(CD);
}


Rover* Mission::getRover()
{
	return rover;
}

bool Mission::completed(int CurrentDay)
{
	return CurrentDay >= CD;
}

void Mission::CalcExcution()
{
	int days_to_reach_target = ceil(2 *(float(TLOC / rover->getSpeed()) / 25)); //A day on Mars is 25 hours
	ED = days_to_reach_target + MDUR;
}

void Mission::CalcCompletion()
{
	CD = ED + FD + WD;
}

void Mission::CalcWaiting(int waiting)
{
	WD = waiting;
}

void Mission::CalcFormulation(int formulation)   //after mission failed
{
	FD = formulation;
}


float Mission::Priority()
{
	priority = 10 * ((getSignificance() / 10.0) + (1.0 / getFormulation()) + (1.0 / (getDuration() * getLocation())));
	if (Location_List == WAITING_LIST)
		return priority;
	else if (Location_List == IN_EXECUTION_LIST)
		return(1.0 / CD);
}

void Mission::incMissionCount()
{
	Missions_Count++;
}
void Mission::decMissionCount()
{
	Missions_Count--;
}