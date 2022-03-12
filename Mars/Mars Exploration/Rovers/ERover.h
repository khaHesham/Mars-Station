#pragma once
#include "Rover.h"

class ERover : public Rover
{
	static int E_count;
	static int E_checkup;
	

public:
	ERover(int rspeed);
	virtual bool endMaintenance(int currentDay);
	static int get_E_count();
	static void set_E_count(int rE_count);
	static int get_E_checkup();
	static void set_E_checkup(int rE_checkup);
};

