#pragma once
#include "Event.h"


class Cancelation : public Event 
{
public : 
    Cancelation(int id, int Ed, MarsStation* rMrsPtr);
    void Excute() const;
    ~Cancelation();
};

