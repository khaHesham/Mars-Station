#pragma once
#include "Event.h"
class Promotion :
    public Event
{
public :
    Promotion(int id, int ED, MarsStation* rMrsPtr);
    void Excute() const;
    ~Promotion() {};
};

