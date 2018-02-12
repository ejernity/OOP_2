#include "flight.h"

using namespace std;

// Constructor
Flight::Flight(string myDestination, time_t myDepartureTime, time_t myFlightDuration, int myEconomyClass, int myLuxuryClass) :
			    destination(myDestination), departureTime(myDepartureTime), flightDuration(myFlightDuration),
				economyClass(myEconomyClass), luxuryClass(myLuxuryClass) {}

// Accessor
int Flight::get_available(int luxury) const
{
	if (luxury)
		return luxuryClass;
	return economyClass;
}

void Flight::cancel_reservations(string ID)
{
	for (unsigned int i = 0; i < passengerList.size(); ++i)
		if (passengerList[i]->get_id() == ID)
		{
			delete passengerList[i];
			passengerList.erase(passengerList.begin() + i);
		}
}

void Flight::add_passenger(Application *newApplication)
{
		this->passengerList.push_back(newApplication);
		if (newApplication->is_luxury_class()) { this->luxuryClass--; }
		else { this->economyClass--; }
}
