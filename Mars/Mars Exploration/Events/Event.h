#pragma once

class MarsStation;

class Event
{
protected:
	int ID; 
	int EventDay;
	MarsStation* MrsPtr;

public :
	Event(int id, int Ed, MarsStation* rMrsPtr) : ID(id), EventDay(Ed),MrsPtr(rMrsPtr) {};
	virtual void  Excute() const = 0 ;
	~Event() {};
	int Get_ID() const
	{
		return ID;
	}
	int getEventDay() const 
	{
		return EventDay; 
	}

};

