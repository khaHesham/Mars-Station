#pragma once
#include "../Defs.h"
#include "../Rovers/Rover.h"
#include<cmath>

class Mission
{
	int FD;
	int WD;
	int ED;
	int CD;

	int TLOC;
	int MDUR;

	int SIG;
	int ID;

	TYPE type;
	Rover* rover;

	static int Missions_Count;

	//Utility functions
	void setTarget(int rTLOC);
	void setDuration(int rMDUR);
	void setSignificance(int rSIG);
	void setID(int id);
	void setformulation(int fd);

protected:
	float priority;
	int Location_List;    //not the best sol but also it will work inshalah

public:
	Mission(int fd, int id, int rTLOC, int rMDUR, int rSIG, TYPE rtype = POLAR, Rover* rrover = nullptr);

	int getFormulation();
	int getWaiting();
	int getexectution();
	int getLocation();
	int getDuration();
	int getSignificance();
	int getID();
	int getCompletion();

	int getM_location();

	void setM_location(int loc);

	TYPE getType();
	static int getCount();
	static void incMissionCount();
	static void decMissionCount();
	Rover* getRover();
	void AssignRover(Rover* rrover);

	void CalcExcution();
	void CalcCompletion();
	void CalcWaiting(int waiting);
	void CalcFormulation(int formulation);   //after mission failed

	bool completed(int CurrentDay);
	//void freeRover();

	float Priority();
};

