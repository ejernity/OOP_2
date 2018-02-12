#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "airport.h"
#include <vector>


using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Please enter only the simulation time" << endl;
		return 2;
	}
	int num;
	time_t curr = 0;
	time_t simulation_time = atoi(argv[1]);
	cout << "Enter number of terminals: ";
	cin >> num;
	
	Airport *myAirport = new Airport(num,curr);

	string str1, str2, str3, str4, str5, str6, str7;

	ifstream myStream;

	myStream.open("airportData.txt", std::ifstream::in);

	getline(myStream, str1);

	while (!myStream.eof())
	{
		myStream >> str1 >> str2 >> str3 >> str4 >> str5;
		if (!myStream.eof())
		{
			int x = atoi(str2.c_str());
			int z = atoi(str3.c_str());
			int i = atoi(str4.c_str());
			int y = atoi(str5.c_str());
			int a = myAirport->add_flight(str1, x, z, i, y);
			if (a == -1)
				break;
		}
	}

	myStream.close();

	myAirport->sorting_flights();

	myStream.open("applicationData.txt", std::ifstream::in);

	getline(myStream, str1);

	while (!myStream.eof())
	{
		myStream >> str1 >> str2 >> str3 >> str4 >> str5 >> str6 >> str7;
		if (!myStream.eof())
		{
			int x = atoi(str5.c_str());
			int y = atoi(str6.c_str());
			if (str7 == "A")
			{
				myAirport->add_application(str1,str2,str3,str4,x,y,true);
			} else { myAirport->add_application(str1,str2,str3,str4,x,y,false); }
 
		}
	}

	myStream.close();

	myAirport->show_timetable();

	//myAirport->show_people_waiting();

	myAirport->flow_time(simulation_time);

	delete myAirport;

	return 0;
}
