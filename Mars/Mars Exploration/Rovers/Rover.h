#pragma once
#include "../Defs.h"

class Rover
{
	TYPE type;
	int speed;
	int mission_count;
	int ID;

	int CD;   //same as mission assigned to it!

	int ROVER_LOCATION;

	static int counter;
	static int rover_count;
	static int N; //number of missions before checkup

	float coveredDistance;
	float nextChkCoveredDist;

protected:
	int checkup_first_Day;

public:
	Rover(int rspeed = 0, TYPE rtype = POLAR);
	bool needsCheckup()const;
	void increment_missions();
	TYPE getType()const;
	int getSpeed()const;
	int GetID();
	int get_checkup_first_Day();
	void set_Rover_Location(int loc);
	void set_checkup_first_Day(int CD);
	void set_CD(int cd);
	float Priority();


	static int get_rover_count();
	static void set_rover_count(int rrover_count);
	static int get_N();
	static void set_N(int rN);

	// for maintenance

	void incCoveredDist(int dist);
	bool NeedsMaintenance();
	float getCoveredDist();
	void setSpeed(int s);
	virtual bool endMaintenance(int currentDay) { return true; };

};

