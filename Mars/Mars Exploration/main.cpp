#include "MarsStation/MarsStation.h"

int main()
{

	MarsStation MS;

	while (MS.NotAllDone())
	{
		MS.HandleDay();

		MS.IncrementDay();
	}

	MS.PrintOutputFile();

	return 0;
}