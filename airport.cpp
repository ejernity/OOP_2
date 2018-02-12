#include <iostream>
#include <cstdlib>
#include "airport.h"

using namespace std;

// Constructor
Airport::Airport(int number_of_terminals, time_t my_current_time) : terminals(number_of_terminals), used_terminals(0), failed_apps(0), currentTime(my_current_time)
{
	terminalArray = new Flight*[number_of_terminals];
	for (int i = 0; i < number_of_terminals; i++)
		terminalArray[i] = NULL;
}

// Destructor
Airport::~Airport()
{
	cout << "\nI just deleted an airport" << endl;
	// Clear flights from all the terminals
	for (int index_of_terminal = 0; index_of_terminal < this->terminals; index_of_terminal++)
	{
	if (terminalArray[index_of_terminal] != NULL)
		// print name-surname of passengers and flight's destination
		for (unsigned int i = 0; i < terminalArray[index_of_terminal]->get_booking().size(); ++i)
		{
			delete (terminalArray[index_of_terminal]->get_booking())[i];
			terminalArray[index_of_terminal]->get_booking().clear();
		}
		delete terminalArray[index_of_terminal];
	}
	// Clear waiting list
	for (list<Application*>::iterator it2 = this->waitingList.begin(); it2 != this->waitingList.end();)
	{	
		delete *it2;
		it2 = this->waitingList.erase(it2);
	}
	// free flights' array
	delete[] terminalArray;
}

// Add application to waiting list
void Airport::add_application(string id, string name, string surname, string destination, time_t arriveToAirport, time_t arriveToDestination, bool isluxury)
{
	Application *application = new Application(id,name,surname,destination,arriveToAirport,arriveToDestination,isluxury);
	int currentTerminal, inserted_to_terminal = 0;
	for (currentTerminal = 0; currentTerminal < this->terminals; currentTerminal++)
		if (terminalArray[currentTerminal] != NULL)
			if (application->matches(*terminalArray[currentTerminal]))
			{	
				// This cout just helped for debugging and be sure that applications that joined a flight are surely joined into this flight
				cout << "I just inserted " << application->get_name() << " to terminal: " << currentTerminal << endl;
				terminalArray[currentTerminal]->add_passenger(application);
				inserted_to_terminal = 1;
				break;
			}
	if (!inserted_to_terminal)
		this->waitingList.push_front(application);
}

// Cancel all ID's applications
void Airport::cancel_applications(string ID)
{
	// cancel applications from waiting list
	for (list<Application*>::iterator it = waitingList.begin(); it != waitingList.end();)
		if ((*it)->get_id() == ID)
		{
			cout << "Delete applications with id: " << ID << " from waiting list" << endl;
			delete *it;
			it = waitingList.erase(it);
			this->failed_apps++;
		} else it++;

	// cancel applications from each flight
	for (int currTerminal = 0; currTerminal < terminals; currTerminal++)
	{
		if (terminalArray[currTerminal] != NULL)
		{
			terminalArray[currTerminal]->cancel_reservations(ID);
			this->failed_apps++;
		}
	}
}

// Add new flight and return corresponding terminal
int Airport::add_flight(string myDestination, time_t myDepartureTime, time_t myFlightDuration, int myEconomyClass, int myLuxuryClass)
{
	int index_of_terminal = 0;
	if (used_terminals < terminals)
	{
		while ((terminalArray[index_of_terminal] != NULL) && (index_of_terminal < terminals)) { index_of_terminal++; }
		this->used_terminals++;
		terminalArray[index_of_terminal] = new Flight(myDestination, myDepartureTime, myFlightDuration, myEconomyClass, myLuxuryClass);
		return index_of_terminal;
	} else return -1;
}

// Flight cancellation
void Airport::cancel_flight(int currentTerminal)
{
	if (terminalArray[currentTerminal] != NULL)
	{
		for (unsigned int i = 0; i < terminalArray[currentTerminal]->get_booking().size(); ++i)
			this->waitingList.push_front((terminalArray[currentTerminal]->get_booking())[i]);
		terminalArray[currentTerminal]->get_booking().clear();
		delete terminalArray[currentTerminal];
		terminalArray[currentTerminal] = NULL;
	}
}

// Print information for all available flights
void Airport::show_timetable()
{
	cout << "Information for available flights:\n" << endl;	// cout explaines what the code above will do
	int current_terminal = 0;
	while (current_terminal < terminals)
	{
		if (terminalArray[current_terminal] != NULL)
		{
			if (terminalArray[current_terminal]->get_available(1) || terminalArray[current_terminal]->get_available(0))	// available A or B classes
			{
				cout << "Terminal: " << current_terminal << endl
				     << "Destination: " << terminalArray[current_terminal]->get_destination() << endl
				     << "Departure time: " << terminalArray[current_terminal]->departs_at() << endl
				     << "Arrival time: " << terminalArray[current_terminal]->arrives_at() << endl
				     << "Luxury classes: " << terminalArray[current_terminal]->get_available(1) << endl
				     << "Economy classes: " << terminalArray[current_terminal]->get_available(0) << endl << endl;
			}
		}
		current_terminal++;
	}
	cout << "Information for all flights:\n" << endl;	// cout explaines what the code above will do
	current_terminal = 0;
	while (current_terminal < terminals)
	{
		if (terminalArray[current_terminal] != NULL)
		{
			cout << "Terminal: " << current_terminal << endl
				 << "Destination: " << terminalArray[current_terminal]->get_destination() << endl
				 << "Departure time: " << terminalArray[current_terminal]->departs_at() << endl
				 << "Arrival time: " << terminalArray[current_terminal]->arrives_at() << endl
				 << "Luxury classes: " << terminalArray[current_terminal]->get_available(1) << endl
				 << "Economy classes: " << terminalArray[current_terminal]->get_available(0) << endl << endl;
		}
		current_terminal++;
	}
}

// Sorting flights
void Airport::sorting_flights()
{
	bool flag;
	for (int i = 1; i < terminals; ++i)
	{
		flag = false;
		for (int current_terminal = 0; current_terminal < terminals - i; current_terminal++)
		{
			if (terminalArray[current_terminal] != NULL && terminalArray[current_terminal+1] != NULL)
				if (terminalArray[current_terminal]->departs_at() > terminalArray[current_terminal+1]->departs_at())
				{
					this->swap(*terminalArray[current_terminal],*terminalArray[current_terminal+1]);
					flag = true;
				}
		}
		if (!flag) break;
	}
}

void Airport::swap(Flight& flight1, Flight& flight2)
{
	Flight temp(flight1);
	flight1 = flight2;
	flight2 = temp;
}

// Print name-surname from people inside the waiting list
void Airport::show_people_waiting()
{
	for (list<Application*>::iterator it = waitingList.begin(); it != waitingList.end(); it++)
	{
		cout << (*it)->get_name() << endl;
	}
}

void Airport::flow_time(time_t simulation_time)
{
	// Testing cancel_applications();
	// If you want to check functionality of this method please remove comments (/*,*/)
	/*
	if (terminalArray[9] != NULL)
	{
		if (!terminalArray[9]->get_booking().empty())
		{
			cout << "Cancel applications for: " << (terminalArray[9]->get_booking())[0]->get_name() << endl;
			cancel_applications((terminalArray[9]->get_booking())[0]->get_id());
		}
	}
	*/
	while (currentTime <= simulation_time)
	{
		// check if a flight is ready to depart
		for (int index_of_terminal = 0; index_of_terminal < terminals; index_of_terminal++)
		{
			if (terminalArray[index_of_terminal] != NULL)
				if (get_time() == terminalArray[index_of_terminal]->departs_at())
				{
					cout << "\nTerminal: " << index_of_terminal << endl;
					// print name-surname of passengers and flight's destination
					for (unsigned int i = 0; i < terminalArray[index_of_terminal]->get_booking().size(); ++i)
					{			
						cout << (terminalArray[index_of_terminal]->get_booking())[i]->get_name() << endl;
						delete (terminalArray[index_of_terminal]->get_booking())[i];
					}
					terminalArray[index_of_terminal]->get_booking().clear();
					cout << terminalArray[index_of_terminal]->get_destination() << endl;
					delete terminalArray[index_of_terminal];
					terminalArray[index_of_terminal] = NULL;
				}
		} 
		// delete applications from waiting list that cannot anymore take a flight
		for (list<Application*>::iterator it2 = this->waitingList.begin(); it2 != this->waitingList.end();)
		{
			if ((*it2)->arrived_by() <= this->get_time())
			{	
				delete *it2;
				it2 = this->waitingList.erase(it2);
			} else 
			{	// cancel_flight and cancel_applications are used only once to be sure for their functionality
				// so there is no big difference in the result and I comment out this for loop for better performance
				/*
				for (int currentTerminal = 0; currentTerminal < terminals; currentTerminal++)
					if (terminalArray[currentTerminal] != NULL)
						if ((*it2)->matches(*terminalArray[currentTerminal]))
						{	
							cout << "I just inserted " << (*it2)->get_name() << " to terminal: " << currentTerminal << " from waiting list" << endl;
							terminalArray[currentTerminal]->add_passenger(*it2);
							break;
						} */
				it2++;
			}
		}
		currentTime++;
		// Testing member function "cancel_flight".
		// If you want to check functionality of this method remove comments (/*,*/)
		/*
		if (currentTime == 60)
			this->cancel_flight(14);
		*/
	}
}