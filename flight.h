#ifndef _FLIGHT_
#define _FLIGHT_

#include <string>
#include <ctime>
#include <vector>
#include "application.h"

using namespace std;

class Application;

class Flight
{
	string destination;
	time_t departureTime;
	time_t flightDuration;
	int economyClass;
	int luxuryClass;
	vector<Application*> passengerList;

public:
	// Constructor
	Flight(string, time_t, time_t, int, int);

	// Add a passenger
	void add_passenger(Application *);

	// Cancel all reservations from a passenger
	void cancel_reservations(string);

	// Accessors
	time_t departs_at() const { return this->departureTime; }
	time_t arrives_at() const { return (this->flightDuration + this->departureTime); }
	string get_destination() const { return this->destination; }
	int get_available(int) const;
	vector<Application*> get_booking() { return passengerList; }
};

#endif
