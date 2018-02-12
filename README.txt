Object Oriented Programming (2017-2018)
Askisi 2 (Airport simulation)
Author: Nikolaos Lamprinos
Registration Number: 1115201600088 (A.M.)

---------------------------------------------

Specific features of my implementation:
1) When a terminal is released I don't add flight. So I read input file once in main function and add flights into my array until it is full.

2) Methods: a) cancel_application() b) cancel_flight()
   I call both once inside method flow_time() to be sure for their functionality.

3) Waiting List: Because of 1) & 2) there is no big difference if I don't compare every application from waiting list to every available flight for all time units of my simulation time.
				 So I commented out this for loop that exists for this specific functionality for better performance (runtime).

4) **WARNING**: The input files are generated from the executable file "generator".

5) I used type time_t for simulation time and other times I need but without convert. Just use it as integer (unit times).

6) My implementation works with an initial time of 00:00.

---------------------------------------------

Instructions:

1) First use generator to create input text files (airportData.txt, applicationData.txt).
   You have to unzip "generator.zip" and then run "chmod 777 generator" to have permission to run "generator".

2) Command for compilation: make

3) You can run: make clean
    and all .o files and executable airportsimulation will be deleted.

4) You have to give only one argument after the name of executable file. This argument is simulation time. For example: ./airportsimulation 1500

---------------------------------------------

Special thanks to Nikolaos Soulounias (1115201600156) for the free distribution of generator.