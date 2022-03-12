#pragma once
#include "Rover.h"

class MRover : public Rover
{
	static int M_count;
	static int M_checkup;

public:
	MRover(int rspeed);
	virtual bool endMaintenance(int currentDay);
	static int get_M_count();
	static void set_M_count(int rM_count);
	static int get_M_checkup();
	static void set_M_checkup(int rM_checkup);
};

