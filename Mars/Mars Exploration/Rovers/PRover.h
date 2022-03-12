#pragma once
#include "Rover.h"

class PRover : public Rover
{
	static int P_count;
	static int P_checkup;

public:
	PRover(int rspeed);
	virtual bool endMaintenance(int currentDay);
	static int get_P_count();
	static void set_P_count(int rP_count);
	static int get_P_checkup();
	static void set_P_checkup(int rP_checkup);
};

