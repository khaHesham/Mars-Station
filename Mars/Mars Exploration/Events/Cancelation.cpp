#include "Cancelation.h"
#include "../MarsStation/MarsStation.h"


Cancelation::Cancelation(int id, int Ed, MarsStation* rMrsPtr) : Event(id, Ed, rMrsPtr)
{

}

void Cancelation::Excute()const
{
	 Mission * mission;
	bool ISfound = MrsPtr->FindMission(ID, mission);
	if (!ISfound) return;
	delete mission;
	Mountainous_Mission::dec_M_COunt();
	Mission::decMissionCount();
}

Cancelation::~Cancelation()
{

}
