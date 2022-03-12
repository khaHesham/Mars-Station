#include "UI.h"
#include "../MarsStation/MarsStation.h"




using namespace std;

UI::UI(MarsStation* rMrsPtr)
{
	MrsPtr = rMrsPtr;

}

void UI::print_current(int CD)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 9);
	cout << "Current Day: ";
	SetConsoleTextAttribute(console, 14);
	cout << CD << endl;
	SetConsoleTextAttribute(console, 15);
}


void UI::print_Day()
{
	print_Waiting();
	print_In_Execution();
	print_Available();
	print_In_checkup();
	print_Completed();
}

void UI::print_Silent()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 8);
	cout << "Silent Mode" << endl;
	cout << "Simulation Starts..." << endl;
	cout << "Simulation ends, Output file created" << endl;
	SetConsoleTextAttribute(console, 15);
}

string UI::ChooseInput()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 11);
	string FileName;
	cout << "\nPlease enter the INPUT file name: ";
	SetConsoleTextAttribute(console, 3);
	cin >> FileName;
	SetConsoleTextAttribute(console, 15);
	return FileName;
}

string UI::ChooseOutput()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 11);
	string FileName;
	cout << "\nPlease enter the OUTPUT file name: ";
	SetConsoleTextAttribute(console, 3);
	cin >> FileName;
	SetConsoleTextAttribute(console, 15);
	return FileName;
}

//COLORS LIST
//1: Blue
//2: Green
//3: Cyan
//4: Red
//5: Purple
//6: Yellow (Dark)
//7: Default white
//8: Gray/Grey
//9: Bright blue
//10: Brigth green
//11: Bright cyan
//12: Bright red
//13: Pink/Magenta
//14: Yellow
//15: Bright white

void UI::print_Waiting()
{
	PriorityQueue<Pair<Mission*>> Emergency = MrsPtr->get_Emergency_Missions();
	LinkedQueue<Mission*> Polar = MrsPtr->get_Polar_Missions();
	LinkedList<Mission*> Mountainous = MrsPtr->get_Mountainous_Missions();
	bool flag = false;
	Mission* tmp;
	Pair<Mission*> M;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


	SetConsoleTextAttribute(console, 9);
	cout << "Waiting Missions: ";
	SetConsoleTextAttribute(console, 6);
	cout << "\t\t[ ";
	while (Emergency.dequeue(M))
	{
		tmp = M.getValue();
		cout << tmp->getID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "]\t";
	SetConsoleTextAttribute(console, 10);
	flag = false;
	cout << "(";
	while (Polar.dequeue(tmp))
	{
		cout << tmp->getID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << ")\t";
	flag = false;
	SetConsoleTextAttribute(console, 11);

	cout << "{";
	int n = Mountainous.getLength();
	for (int i = 1; i <= n; i++)
	{
		tmp = Mountainous.getEntry(i);
		cout << tmp->getID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "}\t";

	SetConsoleTextAttribute(console, 15);
	cout << endl;
	cout << "------------------------------------------------------------\n";
}

void UI::print_In_Execution()
{
	LinkedQueue<Mission*> Emergency;
	LinkedQueue<Mission*> Polar;
	LinkedQueue<Mission*> Mountainous;

	PriorityQueue<Pair<Mission*>> In_execution = MrsPtr->get_InExecution();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


	Mission* tmp;
	Pair<Mission*> M;
	bool flag = false;
	//Data categorization
	while (In_execution.dequeue(M))
	{
		tmp = M.getValue();
		switch (tmp->getType())
		{
		case EMERGENCY:
			Emergency.enqueue(tmp);
			break;
		case MOUNTAINOUS:
			Mountainous.enqueue(tmp);
			break;
		case POLAR:
			Polar.enqueue(tmp);
			break;
		}
	}

	//system("Color 0B");

	SetConsoleTextAttribute(console, 9);
	cout << "In-Execution Missions/Rovers: ";
	SetConsoleTextAttribute(console, 6);

	cout << "  [";
	while (Emergency.dequeue(tmp))
	{
		cout << tmp->getID() << "/" << tmp->getRover()->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "]\t";
	flag = false;
	SetConsoleTextAttribute(console, 10);
	cout << "(";
	while (Polar.dequeue(tmp))
	{
		cout << tmp->getID() << "/" << tmp->getRover()->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << ")\t";
	flag = false;
	SetConsoleTextAttribute(console, 11);
	cout << "{";
	while (Mountainous.dequeue(tmp))
	{
		cout << tmp->getID() << "/" << tmp->getRover()->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "}\t";

	cout << endl;
	SetConsoleTextAttribute(console, 15);
	cout << "------------------------------------------------------------\n";
}

void UI::print_Available()
{
	PriorityQueue<Pair<Rover*>> Emergency = MrsPtr->get_Emergency_Rovers();
	PriorityQueue<Pair<Rover*>> Polar = MrsPtr->get_Polar_Rovers();
	PriorityQueue<Pair<Rover*>> Mountainous = MrsPtr->get_Mountainous_Rovers();
	//	system("Color 0E");
	Rover* tmp;
	Pair<Rover*> R;
	bool flag = false;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, 9);
	cout << "Available Rovers:";
	SetConsoleTextAttribute(console, 6);
	cout << "\t\t[";
	while (Emergency.dequeue(R))
	{
		tmp = R.getValue();
		cout << tmp->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "]\t";
	flag = false;
	SetConsoleTextAttribute(console, 2);
	cout << "(";
	while (Polar.dequeue(R))
	{
		tmp = R.getValue();
		cout << tmp->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << ")\t";
	flag = false;
	SetConsoleTextAttribute(console, 11);
	cout << "{";
	while (Mountainous.dequeue(R))
	{
		tmp = R.getValue();
		cout << tmp->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "}\t";

	SetConsoleTextAttribute(console, 15);
	cout << endl;
	cout << "------------------------------------------------------------\n";
}

void UI::print_In_checkup()
{

	LinkedQueue<Rover*> Emergency = MrsPtr->get_Checkup_Emergency();
	LinkedQueue<Rover*> Polar = MrsPtr->get_Checkup_Polar();
	LinkedQueue<Rover*> Mountainous = MrsPtr->get_Checkup_Mountainous();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	Rover* tmp;
	bool flag = false;

	SetConsoleTextAttribute(console, 9);
	cout << "In-Checkup Rovers:";
	SetConsoleTextAttribute(console, 6);
	cout << "\t\t[";
	while (Emergency.dequeue(tmp))
	{
		cout << tmp->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "]\t";
	flag = false;
	SetConsoleTextAttribute(console, 2);
	cout << "(";
	while (Polar.dequeue(tmp))
	{
		cout << tmp->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << ")\t";
	flag = false;
	SetConsoleTextAttribute(console, 11);
	cout << "{";
	while (Mountainous.dequeue(tmp))
	{
		cout << tmp->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "}\t";

	cout << endl;
	SetConsoleTextAttribute(console, 15);
	cout << "------------------------------------------------------------\n";
}

void UI::print_Completed()
{
	LinkedQueue<Mission*> Emergency;
	LinkedQueue<Mission*> Polar;
	LinkedQueue<Mission*> Mountainous;

	LinkedQueue<Mission*> In_execution = MrsPtr->get_Completed();

	Mission* tmp;
	bool flag = false;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	//Data categorization
	while (In_execution.dequeue(tmp))
	{
		switch (tmp->getType())
		{
		case EMERGENCY:
			Emergency.enqueue(tmp);
			break;
		case MOUNTAINOUS:
			Mountainous.enqueue(tmp);
			break;
		case POLAR:
			Polar.enqueue(tmp);
			break;
		}
	}
	SetConsoleTextAttribute(console, 9);
	cout << "Completed: ";
	SetConsoleTextAttribute(console, 6);
	cout << "\t\t\t[";
	while (Emergency.dequeue(tmp))
	{
		cout << tmp->getID() << "/" << tmp->getRover()->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "]\t";
	flag = false;
	SetConsoleTextAttribute(console, 2);
	cout << "(";
	while (Polar.dequeue(tmp))
	{
		cout << tmp->getID() << "/" << tmp->getRover()->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << ")\t";
	flag = false;
	SetConsoleTextAttribute(console, 11);
	cout << "{";
	while (Mountainous.dequeue(tmp))
	{
		cout << tmp->getID() << "/" << tmp->getRover()->GetID() << ",";
		flag = true;
	}
	if (flag)cout << "\b";
	cout << "}\t";

	cout << endl;
	SetConsoleTextAttribute(console, 15);
	cout << "************************************************************************************************\n\n";
}

MODE UI::ChooseMode()
{
	int mode;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 8);
	cout << "\nPlease choose the mode of operation....\n";
	cout << "[1]-->for Interactive mode\n[2]-->for Step_by_step mode\n[3]-->for Silent mode\t";
	SetConsoleTextAttribute(console, 11);
	cin >> mode;
	cout << endl;
	return MODE(mode - 1);
}

UI::~UI()
{
}