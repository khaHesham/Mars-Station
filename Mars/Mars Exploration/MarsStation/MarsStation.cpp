#include "MarsStation.h"

MarsStation::MarsStation()
{
	promoted_count = 0;
	InOut = new UI(this);
	Read_Input();
	mode = InOut->ChooseMode();
	CurrentDay = 1;
	failed_count = 0;
}

void MarsStation::HandleDay()
{
	ExecuteEvents();
	Checkup();
	Maintenancecheckup();
	ExecutedMissions();
	AssignMissions();
	AutoP();
	Mission_Failure();
	PrintDay();
}

void MarsStation::ExecuteEvents()
{
	Event* Eptr = nullptr;
	while (Events.peek(Eptr))
	{
		if (Eptr->getEventDay() == CurrentDay)
		{
			Eptr->Excute();
			Events.dequeue(Eptr);
			delete Eptr;
		}

		else return;
	}
}


void MarsStation::Checkup()
{

	Rover* Rvrptr = nullptr;

	while (Checkup_Emergency.peek(Rvrptr))
	{
		if (((ERover*)Rvrptr)->get_checkup_first_Day() + ((ERover*)Rvrptr)->get_E_checkup() == CurrentDay)
		{
			Checkup_Emergency.dequeue(Rvrptr);
			Pair<Rover*> R(Rvrptr, Rvrptr->Priority());
			Emergency_Rovers.enqueue(R);
		}
		else break;
	}
	while (Checkup_Polar.peek(Rvrptr))
	{
		if (((PRover*)Rvrptr)->get_checkup_first_Day() + ((PRover*)Rvrptr)->get_P_checkup() == CurrentDay)
		{
			Checkup_Polar.dequeue(Rvrptr);
			Pair<Rover*> R(Rvrptr, Rvrptr->Priority());
			Polar_Rovers.enqueue(R);
		}
		else break;
	}
	while (Checkup_Mountainous.peek(Rvrptr))
	{
		if (((MRover*)Rvrptr)->get_checkup_first_Day() + ((MRover*)Rvrptr)->get_M_checkup() == CurrentDay)
		{
			Checkup_Mountainous.dequeue(Rvrptr);
			Pair<Rover*> R(Rvrptr, Rvrptr->Priority());
			Mountainous_Rovers.enqueue(R);
		}
		else
			break;
	}
}


void MarsStation::AssignRoverToMission(Rover* rover, Mission* mission)
{
	mission->setM_location(IN_EXECUTION_LIST);
	rover->set_Rover_Location(IN_EXECUTION_ROVERS);

	mission->AssignRover(rover);
	rover->increment_missions();
	int waitingDays = CurrentDay - mission->getFormulation();
	mission->CalcWaiting(waitingDays);
	mission->CalcExcution();
	mission->CalcCompletion();

	//sending the covered distance to the rover
	rover->incCoveredDist(2 * mission->getLocation());

	Pair<Mission*> M(mission, mission->Priority());
	Pair<Rover*> R(rover, rover->Priority());
	Pair<Mission*> dummy;


	TYPE type = mission->getType();
	switch (type)
	{
	case EMERGENCY:
		Emergency_Missions.dequeue(dummy);
		break;
	case MOUNTAINOUS:
		Mountainous_Missions.remove(1);
		break;
	case POLAR:
		Polar_Missions.dequeue(mission);
		break;
	}

	RemoveRover(rover);

	InExecution.enqueue(M);
	In_mission_rovers.enqueue(R);
}

void MarsStation::AssignMissions()
{
	Mission* mission;
	Rover* rover;

	Pair<Mission*> M;
	Pair<Rover*> R;

	//Emergency missions assignment..........................................................................................
	while (Emergency_Missions.peek(M)) //i should check here for the mainanence queues 
	{
		mission = M.getValue();
		if (Emergency_Rovers.peek(R))
		{
			rover = R.getValue();
			AssignRoverToMission(rover, mission);
		}
		// if there is no Emergency_rovers check for the rovers in the maintenance
		else if (!Emaintenance.isEmpty())
		{
			//should get it out from the maintenance and decrease its speed and then add it to the mission
			Emaintenance.dequeue(rover);
			rover->setSpeed(rover->getSpeed() / 2);
			AssignRoverToMission(rover, mission);
		}
		else if (Mountainous_Rovers.peek(R))
		{
			rover = R.getValue();
			AssignRoverToMission(rover, mission);
		}
		// if there is no Mountainous_rovers check for the rovers in the maintenance
		else if (!Mmaintenance.isEmpty())
		{
			//should get it out from the maintenance and decrease its speed and then add it to the mission
			Mmaintenance.dequeue(rover);
			rover->setSpeed(rover->getSpeed() / 2);
			AssignRoverToMission(rover, mission);
		}
		else if (Polar_Rovers.peek(R))
		{
			rover = R.getValue();
			AssignRoverToMission(rover, mission);
		}
		// if there is no Polar_rovers check for the rovers in the maintenance
		else if (!Pmaintenance.isEmpty())
		{
			//should get it out from the maintenance and decrease its speed and then add it to the mission
			Pmaintenance.dequeue(rover);
			rover->setSpeed(rover->getSpeed() / 2);
			AssignRoverToMission(rover, mission);
		}

		else break;
	}


	//Polar Mission assignment..............................................................................................
	while (Polar_Missions.peek(mission))//i should check here for the mainanence queues 
	{
		if (Polar_Rovers.peek(R))
		{
			rover = R.getValue();
			AssignRoverToMission(rover, mission);
		}
		else if (!Pmaintenance.isEmpty())
		{
			//should get it out from the maintenance and decrease its speed and then add it to the mission
			Pmaintenance.dequeue(rover);
			rover->setSpeed(rover->getSpeed() / 2);
			AssignRoverToMission(rover, mission);
		}
		else break;
	}
	//Mountainous missions assignment............................................................................................
	while (!Mountainous_Missions.isEmpty())//i should check here for the mainanence queues 
	{
		mission = Mountainous_Missions.getEntry(1);
		if (Mountainous_Rovers.peek(R))
		{
			rover = R.getValue();
			AssignRoverToMission(rover, mission);
		}
		else if (!Mmaintenance.isEmpty())
		{
			//should get it out from the maintenance and decrease its speed and then add it to the mission
			Mmaintenance.dequeue(rover);
			rover->setSpeed(rover->getSpeed() / 2);
			AssignRoverToMission(rover, mission);
		}
		else if (Emergency_Rovers.peek(R))
		{
			rover = R.getValue();
			AssignRoverToMission(rover, mission);
		}
		else if (!Emaintenance.isEmpty())
		{
			//should get it out from the maintenance and decrease its speed and then add it to the mission
			Emaintenance.dequeue(rover);
			rover->setSpeed(rover->getSpeed() / 2);
			AssignRoverToMission(rover, mission);
		}

		else break;
	}

}

void MarsStation::AutoP()
{
	//lw el current day > fd + autoP ha7wl el mountainous l emergency
	//Mountainous_Missions.getEntry
	while (!Mountainous_Missions.isEmpty())
	{
		Mission* MMptr = Mountainous_Missions.getEntry(1);
		//	MMptr->decMissionCount();
		if (CurrentDay >= MMptr->getFormulation() + Mountainous_Mission::getAutoP())
		{
			promoted_count++;
			int Fd = MMptr->getFormulation();
			int ID = MMptr->getID();
			int TLOC = MMptr->getLocation();
			int DUR = MMptr->getDuration();
			int SGN = MMptr->getSignificance();

			delete MMptr; //delete the mountaious mission
			Mountainous_Missions.remove(1);//delete from the node 

			//creat new emergency mission
			MMptr = new Emergency_Mission(Fd, ID, TLOC, DUR, SGN);

			AddMission(MMptr);
		}
		else break;
	}

}
void MarsStation::Maintenancecheckup()
{
	Rover* Rvrptr = nullptr;
	while (Emaintenance.peek(Rvrptr))
	{
		if (Rvrptr->endMaintenance(CurrentDay))
		{
			Emaintenance.dequeue(Rvrptr);
			Pair<Rover*> R(Rvrptr, Rvrptr->Priority());
			Emergency_Rovers.enqueue(R);
		}
		else break;
	}

	while (Pmaintenance.peek(Rvrptr))
	{
		if (Rvrptr->endMaintenance(CurrentDay))
		{
			Pmaintenance.dequeue(Rvrptr);
			Pair<Rover*> R(Rvrptr, Rvrptr->Priority());
			Polar_Rovers.enqueue(R);
		}
		else break;
	}

	while (Mmaintenance.peek(Rvrptr))
	{
		if (Rvrptr->endMaintenance(CurrentDay))
		{
			Mmaintenance.dequeue(Rvrptr);
			Pair<Rover*> R(Rvrptr, Rvrptr->Priority());
			Mountainous_Rovers.enqueue(R);
		}
		else break;
	}


}
void MarsStation::maintenance(Rover* R1)
{
	//apart from their regular checkups 
	//so i need to make a special type of checkup list  for maintenance
	if (R1->getType() == MOUNTAINOUS)
	{
		Mmaintenance.enqueue(R1);
	}
	else if (R1->getType() == POLAR)
	{
		Pmaintenance.enqueue(R1);
	}
	else
		Emaintenance.enqueue(R1);
}
void MarsStation::ExecutedMissions()
{
	Mission* mission;
	Pair<Mission*> M;
	Pair<Rover*> R;

	while (InExecution.peek(M))
	{
		mission = M.getValue();
		if (mission->completed(CurrentDay))
		{
			Rover* rover = mission->getRover();

			if (rover->needsCheckup())
				MoveToCheckup(rover);
			else if (rover->NeedsMaintenance())
				maintenance(rover);
			else
				AddRover(rover);

			In_mission_rovers.dequeue(R);

			InExecution.dequeue(M);
			Completed.enqueue(mission);
		}

		else return;
	}
}

void MarsStation::Mission_Failure()
{
	Mission* failed = nullptr;
	Pair<Mission*> M;

	float Random = ((double)rand() / (RAND_MAX));   //Generate random number between [0,1]      choose probability to fail = 2% maxiumum 

	if (0.0125 < Random < 0.0130)
	{
		if (InExecution.peek(M))  //Mission failed    2% max
		{
			failed_count++;
			InExecution.dequeue(M);
			failed = M.getValue();

			MoveToCheckup(failed->getRover());    //move Rover to checkup


			//calculations of time 
			int formulationDay = CurrentDay + 1;
			failed->CalcFormulation(formulationDay);

			AddMission(failed);

		}
		else
			return;
	}

	//NOTES:
	//[*] I chossed numbers based on my point of view this numbers do not mean spacific logic.
	//[*] You can notice that probability of emergancy miision to fail is very small because in real life
	//Emergancy Rovers are  are highly efficient and works well rather than in any other rover.  (when duty calls nothing stops them ;)  )
}

void MarsStation::PrintDay()
{
	if (mode == INTERACTIVE)
	{
		char c;
		c = fgetc(stdin); //read a single char
		if (c == 0x0A)
		{
			InOut->print_current(CurrentDay);
			InOut->print_Day();
		}
	}
	else if (mode == STEP_BY_STEP)
	{
		InOut->print_current(CurrentDay);
		InOut->print_Day();
		Sleep(1000); //waiting for 1 sec
	}

	if (!NotAllDone())
	{
		if (mode == SILENT)
			InOut->print_Silent();
	}
}
void MarsStation::PrintOutputFile()
{
	float Avg_Wait = 0, Avg_Exec = 0;

	ofstream out;
	Mission* tmp;

	string FileName = InOut->ChooseOutput();
	string path = "./Test Cases/Output files/" + FileName + ".txt";

	out.open(path);

	out << "CD\tID\tFD\tWD\tED\n";
	while (Completed.dequeue(tmp))
	{
		Avg_Wait += tmp->getWaiting();
		Avg_Exec += tmp->getexectution();

		out << tmp->getCompletion() << "\t" << tmp->getID() << "\t" << tmp->getFormulation() << "\t" << tmp->getWaiting() << "\t" << tmp->getexectution() << endl;
	}

	out << "\n.....................................\n";
	out << ".....................................\n";

	out << "Missions :" << Mission::getCount() << " [M: " << Mountainous_Mission::getM_Count() << ", P:" << Polar_Mission::getP_Count() << ", E:" << Emergency_Mission::getE_Count() << " ]" << endl;
	out << "Rovers : " << Rover::get_rover_count() << " [M: " << MRover::get_M_count() << ", P:" << PRover::get_P_count() << ", E:" << ERover::get_E_count() << " ]" << endl;

	out << "Avg Wait = " << Avg_Wait / (Mission::getCount()) << " Avg Exec = " << Avg_Exec / (Mission::getCount()) << endl;

	out << "Auto-promoted: " << ((float)promoted_count / Mountainous_Mission::getM_Count()) * 100 << "%\n";

	out << "Failed Missions :" << failed_count << endl;

	out.close();
}

void MarsStation::IncrementDay()
{
	CurrentDay++;
}

bool MarsStation::NotAllDone()
{


	if (!Events.isEmpty() || !Polar_Missions.isEmpty() || !Emergency_Missions.isEmpty()
		|| !Mountainous_Missions.isEmpty() || !Checkup_Emergency.isEmpty()
		|| !Checkup_Mountainous.isEmpty() || !Checkup_Polar.isEmpty()
		|| !InExecution.isEmpty())
		// if any of these lists isn't empty then we still have work to do 
	{
		return true;

	}
	else
	{
		return false;
	}
}

void MarsStation::RemoveRover(Rover* rover)
{
	TYPE type = rover->getType();
	Pair<Rover*> R;
	switch (type)
	{
	case EMERGENCY:
		Emergency_Rovers.dequeue(R);
		break;
	case MOUNTAINOUS:
		Mountainous_Rovers.dequeue(R);
		break;
	case POLAR:
		Polar_Rovers.dequeue(R);
		break;
	}
}

void MarsStation::AddRover(Rover* rover)
{
	TYPE type = rover->getType();
	Pair<Rover*> R(rover, rover->getSpeed());
	switch (type)
	{
	case EMERGENCY:
		Emergency_Rovers.enqueue(R);
		break;
	case MOUNTAINOUS:
		Mountainous_Rovers.enqueue(R);
		break;
	case POLAR:
		Polar_Rovers.enqueue(R);
		break;
	}
}

void MarsStation::MoveToCheckup(Rover* rover)
{
	TYPE type = rover->getType();

	rover->set_checkup_first_Day(CurrentDay);

	switch (type)
	{
	case EMERGENCY:
		Checkup_Emergency.enqueue(rover);
		break;
	case MOUNTAINOUS:
		Checkup_Mountainous.enqueue(rover);
		break;
	case POLAR:
		Checkup_Polar.enqueue(rover);
		break;
	}
}

void MarsStation::AddMission(Mission* mission)
{
	TYPE type = mission->getType();

	switch (type)
	{
	case EMERGENCY:
	{
		Pair<Mission*> M(mission, mission->Priority());
		Emergency_Missions.enqueue(M);
		break;
	}
	case MOUNTAINOUS:
	{
		int counter = Mountainous_Missions.getLength();
		Mountainous_Missions.insert(counter + 1, mission);
	}
	break;
	case POLAR:
		Polar_Missions.enqueue(mission);
		break;
	}
}


bool MarsStation::FindMission(int ID, Mission*& mission)
{

	int n = Mountainous_Missions.getLength();
	for (int i = 1; i <= n; i++)
	{
		mission = Mountainous_Missions.getEntry(i);
		if (mission->getID() == ID)
		{
			Mountainous_Missions.remove(i);
			return true;
		}
	}
	return false;
}

void MarsStation::Read_Input()
{
	string FileName = InOut->ChooseInput();
	/*cout << "Please enter the INPUT file name: ";
	cin >> FileName;*/
	string path = "./Test Cases/Input files/" + FileName + ".txt";
	ifstream file;
	file.open(path);

	if (!file.is_open()) // if it can't open it
	{
		return;
	}


	int NoOfMount; // no of mount rovers
	file >> NoOfMount;
	MRover::set_M_count(NoOfMount);
	int* Mspeed = new int[NoOfMount]; // array to store the speed
	for (int i = 0; i < NoOfMount; i++)
		file >> Mspeed[i];


	// no of emerg rovers
	int NoOfEmerg;
	file >> NoOfEmerg;
	ERover::set_E_count(NoOfEmerg);
	int* Espeed = new int[NoOfEmerg];
	for (int i = 0; i < NoOfEmerg; i++)
		file >> Espeed[i];

	// no of pol rovers
	int NoOfPol;
	file >> NoOfPol;
	PRover::set_P_count(NoOfPol);
	int* Pspeed = new int[NoOfPol];
	for (int i = 0; i < NoOfPol; i++)
		file >> Pspeed[i];

	Rover::set_rover_count(NoOfEmerg + NoOfPol + NoOfMount);

	//no of missions before checkup
	int NOMBC;
	file >> NOMBC;

	// static member function
	Rover::set_N(NOMBC);

	//checkup durations 
	int CM, CP, CE;
	file >> CM >> CP >> CE;
	MRover::set_M_checkup(CM);
	PRover::set_P_checkup(CP);
	ERover::set_E_checkup(CE);

	//Autop -> number of days after which the mountanious mission is automatically promoted 
	int AutoP;
	file >> AutoP;
	Mountainous_Mission::setAutoP(AutoP);
	// no of events in the file 
	int Eventsnum;
	file >> Eventsnum;

	//creation of Mrovers
	for (int i = 0; i < NoOfMount; i++)
	{
		MRover* Mptr = new MRover(Mspeed[i]);
		AddRover(Mptr);
	}

	//creation of Provers
	for (int i = 0; i < NoOfPol; i++)
	{
		PRover* Pptr = new PRover(Pspeed[i]);
		AddRover(Pptr);
	}

	//creation of Erovers
	for (int i = 0; i < NoOfEmerg; i++)
	{
		ERover* Eptr = new ERover(Espeed[i]);
		AddRover(Eptr);
	}

	//iterating on all events
	for (int i = 0; i < Eventsnum; i++)
	{
		char typeEv;   // type of the event
		file >> typeEv;

		if (typeEv == 'F' || typeEv == 'f')  // formulation event
		{
			Mission::incMissionCount();
			//READING DATA
			char typeM; // type of the missions 
			file >> typeM;

			int eventday;
			file >> eventday;

			int ID;  //no more than one mission can have the same ID
			file >> ID;

			int TLOC; //targetLoc
			file >> TLOC;

			int MDUR; // no of days needed to fulfill the missions 
			file >> MDUR;

			int SIG; // mission significance 
			file >> SIG;

			//DETERMINE WHICH TYPE SHOULD WORK ON
			if (typeM == 'M' || typeM == 'm') // mount
			{
				//Formulation(TYPE rtype, int rTLOG, int rSIG, int rMDUR, int id, int ED, MarsStation * rMrsPtr);
				Event* Fptr = new Formulation(MOUNTAINOUS, TLOC, SIG, MDUR, ID, eventday, this);
				Events.enqueue(Fptr);
				Mountainous_Mission::inc_M_COunt();
			}
			else if (typeM == 'P' || typeM == 'p') // polar
			{
				Event* Fptr = new Formulation(POLAR, TLOC, SIG, MDUR, ID, eventday, this);
				Events.enqueue(Fptr);
				Polar_Mission::inc_P_Count();
			}
			else if (typeM == 'E' || typeM == 'e') // emerg
			{
				Event* Fptr = new Formulation(EMERGENCY, TLOC, SIG, MDUR, ID, eventday, this);
				Events.enqueue(Fptr);
				Emergency_Mission::inc_E_count();
			}
			continue;
		}

		else if (typeEv == 'X' || typeEv == 'x') //cancelation event
		{
			int eventday;
			file >> eventday;
			int ID;  //no more than one mission can have the same ID
			file >> ID;
			Event* Cptr = new Cancelation(ID, eventday, this);
			Events.enqueue(Cptr);
			continue;
		}

		else if (typeEv == 'P' || typeEv == 'p') // promotion event
		{
			int eventday;
			file >> eventday;
			int ID;  //no more than one mission can have the same ID
			file >> ID;
			Event* Pptr = new Promotion(ID, eventday, this); // creat event and enqueue in the lis
			Events.enqueue(Pptr);
			continue;
		}
	}

	file.close(); // closing the file 
}

//Getters

PriorityQueue<Pair<Mission*>> MarsStation::get_InExecution() { return InExecution; }
LinkedQueue<Mission*> MarsStation::get_Completed() { return Completed; }

LinkedQueue<Mission*> MarsStation::get_Polar_Missions() { return Polar_Missions; }
PriorityQueue<Pair<Mission*>> MarsStation::get_Emergency_Missions() { return Emergency_Missions; }
LinkedList<Mission*> MarsStation::get_Mountainous_Missions() { return Mountainous_Missions; }

PriorityQueue<Pair<Rover*>> MarsStation::get_Emergency_Rovers() { return Emergency_Rovers; }
PriorityQueue<Pair<Rover*>> MarsStation::get_Mountainous_Rovers() { return Mountainous_Rovers; }
PriorityQueue<Pair<Rover*>> MarsStation::get_Polar_Rovers() { return Polar_Rovers; }

LinkedQueue<Rover*> MarsStation::get_Checkup_Emergency() { return Checkup_Emergency; }
LinkedQueue<Rover*> MarsStation::get_Checkup_Mountainous() { return Checkup_Mountainous; }
LinkedQueue<Rover*> MarsStation::get_Checkup_Polar() { return Checkup_Polar; }

MarsStation::~MarsStation()
{
	ClearQueue(Completed);

	//clearing priorityqueues
	ClearPQueue(Emergency_Rovers);
	ClearPQueue(Mountainous_Rovers);
	ClearPQueue(Polar_Rovers);

	delete InOut;
}

template <class zuz>
void MarsStation::ClearQueue(LinkedQueue<zuz*> Q)
{
	while (!Q.isEmpty())
	{
		zuz* deleteptr;
		Q.dequeue(deleteptr);
		delete deleteptr;
	}
	//-> House termination
}

template <class zuz>
void MarsStation::ClearPQueue(PriorityQueue<Pair<zuz*>> Q)
{
	Pair<zuz*> p;
	while (!Q.isEmpty())
	{
		Q.dequeue(p);
		zuz* deleteptr = p.getValue();
		delete deleteptr;
	}
}
