#pragma once
#include "../Defs.h"
#include <windows.h>  
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;


class MarsStation;

class UI
{
	MarsStation* MrsPtr;

	// Utility functions
	
	void print_Waiting();
	void print_In_Execution();
	void print_Available();
	void print_In_checkup();
	void print_Completed();

public:
	UI(MarsStation* rMrsPtr);
	void print_current(int CD);
	void print_Day();
	void print_Silent();
	string ChooseInput();
	string ChooseOutput();
	
	MODE ChooseMode();
	~UI();
};

