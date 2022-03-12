#pragma once
#include "../Defs.h"
#include "../ADTs/LinkedQueue.h"
#include "../ADTs/PeriorityQueue.h"
#include "../ADTs/LinkedList.h"

#include "../Events/Event.h"
#include"../Events/Cancelation.h"
#include"../Events/Formulation.h"
#include"../Events/Promotion.h"

#include "../UI/UI.h"
#include "../pair.h"

#include "../Rovers/Rover.h"
#include"../Rovers/ERover.h"
#include"../Rovers/MRover.h"
#include"../Rovers/PRover.h"

#include "../Missions/Mission.h"
#include "../Missions/Emergency_Mission.h"
#include "../Missions/Polar_Mission.h"
#include "../Missions/Mountainous_Mission.h"

#include<fstream>
#include<Windows.h>

class MarsStation
{
	UI* InOut;
	int CurrentDay;
	MODE mode;

	//int count;   // counter used in mountinous List.
	int promoted_count;

	int failed_count;

	//All lists

	LinkedQueue<Event*> Events;

	PriorityQueue<Pair<Rover*>> Emergency_Rovers;
	PriorityQueue<Pair<Rover*>> Mountainous_Rovers;
	PriorityQueue<Pair<Rover*>> Polar_Rovers;

	LinkedQueue<Rover*> Checkup_Emergency;
	LinkedQueue<Rover*> Checkup_Mountainous;
	LinkedQueue<Rover*> Checkup_Polar;

	LinkedQueue<Mission*> Polar_Missions;
	PriorityQueue<Pair<Mission*>> Emergency_Missions;
	LinkedList<Mission*> Mountainous_Missions;

	PriorityQueue<Pair<Mission*>> InExecution;
	PriorityQueue<Pair<Rover*>> In_mission_rovers;
	LinkedQueue<Mission*> Completed;

	//apart from the checkup
	LinkedQueue<Rover*> Emaintenance;
	LinkedQueue<Rover*> Pmaintenance;
	LinkedQueue<Rover*> Mmaintenance;


	//UTILITY FUNCTIONS

	void AssignRoverToMission(Rover* rover, Mission* mission);

	///
	template <class zuz>
	void ClearQueue(LinkedQueue<zuz*> Q);
	template <class zuz>
	void ClearPQueue(PriorityQueue<Pair<zuz*>> Q);

public:

	MarsStation();
	void Checkup();
	void AssignMissions();
	void ExecutedMissions();
	void Mission_Failure();
	void PrintDay();
	void PrintOutputFile();
	void IncrementDay();
	void HandleDay();
	void AddRover(Rover* rover);
	void MoveToCheckup(Rover* rover);
	void AddMission(Mission* mission);
	bool FindMission(int ID, Mission*& mission);
	void RemoveRover(Rover* rover);

	/// ///////////////////////
	//zuz work
	void Maintenancecheckup();
	void maintenance(Rover* R1);
	void Read_Input();
	void AutoP();
	void ExecuteEvents();
	bool NotAllDone();

	PriorityQueue<Pair<Mission*>> get_InExecution();
	LinkedQueue<Mission*> get_Completed();


	LinkedQueue<Mission*> get_Polar_Missions();
	PriorityQueue<Pair<Mission*>> get_Emergency_Missions();
	LinkedList<Mission*> get_Mountainous_Missions();


	PriorityQueue<Pair<Rover*>> get_Emergency_Rovers();
	PriorityQueue<Pair<Rover*>> get_Mountainous_Rovers();
	PriorityQueue<Pair<Rover*>> get_Polar_Rovers();


	LinkedQueue<Rover*> get_Checkup_Emergency();
	LinkedQueue<Rover*> get_Checkup_Mountainous();
	LinkedQueue<Rover*> get_Checkup_Polar();

	//apart from the checkup
	


	~MarsStation();
};

