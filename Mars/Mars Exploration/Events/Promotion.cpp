#include "Promotion.h"
#include "../MarsStation/MarsStation.h"

Promotion::Promotion(int id, int Ed, MarsStation* rMrsPtr) : Event(id, Ed, rMrsPtr)
{

}

void Promotion::Excute() const
{
	Mission* mission;
	bool found = MrsPtr->FindMission(ID, mission);
	if (!found) return;

	int FD = mission->getFormulation();
	int ID = mission->getID();
	int TLOC = mission->getLocation();
	int MDUR = mission->getDuration();
	int SIG = mission->getSignificance();
	delete mission;

	mission = new Emergency_Mission(FD, ID, TLOC, MDUR, SIG);
	MrsPtr->AddMission(mission);
}