#include "Formulation.h"

Formulation::Formulation(TYPE rtype, int rTLOG, int rSIG, int rMDUR, int id, int ED, MarsStation* rMrsPtr)
	:Event(id, ED, rMrsPtr), type(rtype), TLOC(rTLOG), SIG(rSIG), MDUR(rMDUR)
{

}

void Formulation::Excute() const   //create new mission --->list of missions
{
	//int fd, int id, int rTLOC, int rMDUR, int rSIG)
	Mission* misptr = nullptr;
	switch (type)
	{
	case(EMERGENCY):
		misptr = new Emergency_Mission(EventDay,ID, TLOC, MDUR, SIG);
		break;
	case(POLAR):
		misptr = new Polar_Mission(EventDay, ID, TLOC, MDUR, SIG);
		break;
	case(MOUNTAINOUS):
		misptr = new Mountainous_Mission(EventDay, ID, TLOC, MDUR, SIG);
		break;
	}

	MrsPtr->AddMission(misptr);
}


Formulation::~Formulation()
{

}

