#ifndef _AIRPORT_
#define _AIRPORT_

#include "flight.h"
#include "application.h"
#include <ctime>
#include <list>

class Flight;

class Airport
{
	int terminals;
	int used_terminals;
	int failed_apps;
	time_t currentTime;
	Flight** terminalArray;
	list<Application*> waitingList;

public:
	// Constructor
	Airport(int, time_t);

	// Destructor
	~Airport();

	// Accessors
	time_t get_time() const { return this->currentTime; }

	// Add application to waiting list
	void add_application(string,string,string,string,time_t,time_t,bool);

	// Delete all ID's applications
	void cancel_applications(string);

	// Add new flight and return corresponding terminal
	int add_flight(string, time_t, time_t, int, int);

	// Flight cancellation
	void cancel_flight(int);		// pairnei os orisma to antistoixo terminal

	// recover the number of canceled applications
	inline int failed_applications() const { return this->failed_apps; }

	// Print available flights and their information by the order of departure
	void show_timetable();

	// Print name-surname from people inside the waiting list
	void show_people_waiting();

	// it moves the time with the time we set
	void flow_time(time_t);

	// sorting flights
	void sorting_flights();

	// swap
	void swap(Flight&, Flight&);
};

#endif
