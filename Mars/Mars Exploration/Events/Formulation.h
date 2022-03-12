#pragma once
#include "Event.h"
#include "../Missions/Mission.h"
#include "../Defs.h"
#include "../MarsStation/MarsStation.h"

class Formulation : public Event
{
    TYPE type; 
    int TLOC;
    int SIG;
    int MDUR; 
public :
    Formulation(TYPE rtype, int rTLOG, int rSIG, int rMDUR , int id, int ED, MarsStation* rMrsPtr);
    void Excute() const;
    ~Formulation();
};

