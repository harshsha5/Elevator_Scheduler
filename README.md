# Elevator_Scheduler

Compilation Instructions: 
g++ -std=c++11 -O1 main.cpp passenger.cpp Elevator.cpp -o candidate_solution

Running Instructions: 
./candidate_solution

Program Overview: 

This program is an elevator scheduler. Input variables:

1. Elevator Speed
2. Total number of people who will be using the elevator
3. Number of elevators
4. Pickup and Drop off time
5. Number of floors in the building
6. Maximum capacity of an elevator
7. Passenger schedule (Includes Passenger start and end floor along with the start time)

Output
1. End Time for each of the passenger
2. Minimization of summation of passengers total times

Code Structure

1. Passenger Class: Tracks all passenger information including start and end time
2. Elevator Class: Maintains a priority queue of the passengers on board
3. Main: The main contains the most important logic loop, whose structure is as follows

		-Update Elevator for passenger drop-offs
		-Add passengers from schedule list to active passengers list (based on the present_time)
		-Allocate Elevator to each passenger
		-Board Passengers appropriately into elevator

Note to reader: 

The input can be changed from input.h file


