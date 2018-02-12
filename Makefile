airportsimulation: main.o airport.o flight.o application.o
	g++ main.o airport.o flight.o application.o -o airportsimulation

main.o: main.cpp
	g++ -c main.cpp

airport.o: airport.cpp airport.h
	g++ -c airport.cpp

flight.o: flight.cpp flight.h
	g++ -c flight.cpp

application.o: application.cpp application.h
	g++ -c application.cpp

clean:
	rm *.o airportsimulation