#ifndef _APPLICATION_
#define _APPLICATION_

#include <iostream>
#include <cstring>
#include <ctime>
#include "flight.h"

using namespace std;

class Flight;

class Application
{
	string ID;
	string name;
	string surname;
	string destination;
	time_t timeToAirport;
	time_t timeToDestination;
	bool luxuryClass;	// if true, is luxury class, else economy class

public:
	// Constructor
	Application(string, string, string, string, time_t, time_t, bool);

	// Function to compare Application - Flight
	bool matches(const Flight&);

	// Accessors
	bool is_luxury_class() const { return this->luxuryClass; }
	string get_id() const { return this->ID; }
	string get_name() const { return (this->name + " " + this->surname); }
	time_t arrived_by() const { return this->timeToDestination; }
};

#endif