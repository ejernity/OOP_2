#include "application.h"

// Constructor
Application::Application(string myID, string myName, string mySurname, string myDestination, time_t myTimeToAirport,
						time_t myTimeToDestination, bool myLuxuryClass) : 
						ID(myID), name(myName), surname(mySurname), destination(myDestination),
						timeToAirport(myTimeToAirport), timeToDestination(myTimeToDestination),
						luxuryClass(myLuxuryClass) {}

// Function to compare Application - Flight
bool Application::matches(const Flight& currFlight)
{
	if (this->destination == currFlight.get_destination())		// application's destination is the same as flight's destination
	{
		if (this->timeToAirport <= currFlight.departs_at())	// passenger is getting ahead of this flight
		{
			if (this->timeToDestination >= currFlight.arrives_at())	// passenger will arrive destination before or exactly the time he/she desires
			{
				if (currFlight.get_available(this->is_luxury_class()))	// and flight has available luxury class
					return true;
			}
		}
	}
	return false;		// application doesn't match to current flight
}