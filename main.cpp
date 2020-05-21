#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include "input.h"
#include "Passenger.h"
#include "Elevator.h"

using namespace std;
//=====================================================================================================================

void  deallocate_passenger_from_elevator(Passenger &p, Elevator &e)
{
    p.board_start_time=-1;    //Reinitialize the board start time
    p.allotted_elevator=-1;    //Allocate the person a new elevator
    e.reduce_pcount();  //The elevator is not picking that person anymore
}

//=====================================================================================================================

int main() {
    //Note time is in integral seconds

    int PRESENT_TIME{0};
    int num_passengers_reached{0};
    int passenger_in_vec_counter{0};
    Elevator init_elevator(1);
    vector<Elevator> elevators(NUM_ELEVATORS,init_elevator);    //Maintains status of each elevator
    vector<int> active_elevators;   //Elevators which are moving
    vector<Passenger> dropping_passengers;
    vector<Passenger> dropped_passengers;

    if(NUM_PASSENGERS!=PASSENGERS.size())
    {
        cout<<"Input is wrong. Number of passengers, don't match size of passenger input"<<endl;
        return 0;
    }

    vector<int> idle_elevators;
    for(int i=0;i<NUM_ELEVATORS;i++)   //Elevator count is 0 indexed...
    {
        idle_elevators.push_back(i);
    }

    vector<Passenger> active_total_passengers; //Passengers that have atleast reached the elevator based on the time

    while(num_passengers_reached<NUM_PASSENGERS)
    {
        cout<<"Present Time is: "<<PRESENT_TIME<<endl;

        //This part handles the dropping passengers
        for(int i=0;i<dropping_passengers.size();i++)
        {
            if(PRESENT_TIME - dropping_passengers[i].dropoff_start_time == PDO_TIME)   //If the passenger has waited for the PDO time, move it to dropped passengers
            {
                auto dropped_passenger = dropping_passengers[i];
                dropped_passenger.end_time = PRESENT_TIME;
                dropping_passengers.erase(dropping_passengers.begin()+i);
                i--;
                std::cout<<"Completely dropped off passenger"<<std::endl;
                std::cout<<"Getting passenger drop details: "<<std::endl;
                std::cout<<"Passenger End time: "<<dropped_passenger.end_time<<std::endl;
                dropped_passengers.push_back(std::move(dropped_passenger));
                num_passengers_reached++;
            }
        }


        //This part handles elevator floor updates and passenger drop offs from the elevator
        for(int i=0;i<active_elevators.size();i++)
        {
            auto ind = active_elevators[i];
            cout<<"Active elevators size: "<<active_elevators.size()<<endl;
            if(elevators[ind].elevator_status==NONE)    //If boarding/dropping_off, then lift doesn't move
            {
                elevators[ind].time_since_start++;          //If not boarding the timer increases
                if(elevators[ind].time_since_start % TIME_TO_COVER_FLOOR ==0)
                {
                    elevators[ind].update_floor();
                    std::cout<<"Printing info for elevator: "<<ind<<std::endl;
                    elevators[ind].compact_print();
                }

                while(!elevators[ind].pq.empty() && elevators[ind].pq.top().end_floor == elevators[ind].floor)
                {
                    elevators[ind].elevator_status = DROPOFF;
                    elevators[ind].dropoff_time = 0;
                    auto top_passenger = elevators[ind].pq.top();
                    top_passenger.dropoff_start_time = PRESENT_TIME;
                    elevators[ind].pq.pop();
                    std::cout<<"Dropping Off Passenger.."<<std::endl;
                    top_passenger.compact_print();
                    dropping_passengers.push_back(std::move(top_passenger));
                }
            }
            else if(elevators[ind].elevator_status==DROPOFF)
            {
                std::cout<<"Printing info for elevator: "<<ind<<std::endl;
                elevators[ind].compact_print();
                elevators[ind].dropoff_time++;
                if(elevators[ind].dropoff_time - PDO_TIME==0)
                {
                    elevators[ind].post_drop_reset();
                    if(elevators[ind].pq.empty())
                    {
                        std::cout<<"Elevator has dropped off all passengers. Setting elevator to idle"<<std::endl;
                        elevators[ind].set_idle();
                        active_elevators.erase(std::remove(active_elevators.begin(), active_elevators.end(), ind), active_elevators.end());
                        idle_elevators.push_back(ind);
                        i--;
                    }
                }
            }
        }


        while(true) //This loop puts passengers from the overall list to the active list
        {
            if(passenger_in_vec_counter>=PASSENGERS.size() || PASSENGERS[passenger_in_vec_counter][0]>PRESENT_TIME)
                break;
            else if(PASSENGERS[passenger_in_vec_counter][0] == PRESENT_TIME)
            {
                Passenger p{PRESENT_TIME,PASSENGERS[passenger_in_vec_counter][1],PASSENGERS[passenger_in_vec_counter][2]};
                p.compute_direction();
                active_total_passengers.push_back(std::move(p));
                passenger_in_vec_counter++;
            }
        }

        for(auto &passenger:active_total_passengers) //This loop tries to allocate each passenger in the active list an elevator.
        {
            if(passenger.allotted_elevator==-1)
            {
                for(const auto &j:active_elevators)     //First let's see if any active elevator can be utilised
                {
                    if(elevators[j].assigned_pdirn == passenger.direction && elevators[j].num_people()<MAX_CAPACITY)
                    {
                        if(elevators[j].direction==UP && elevators[j].floor<=passenger.start_floor)
                        {
                            passenger.allotted_elevator=j;
                            elevators[j].assigned_pcount++;
                            break;
                        }
                        else if(elevators[j].direction==DOWN && elevators[j].floor>=passenger.start_floor)
                        {
                            passenger.allotted_elevator=j;
                            elevators[j].assigned_pcount++;
                            break;
                        }

                    }
                    if(passenger.allotted_elevator!=-1) //Elevator has been allotted to passenger, no need to search further
                        break;
                }
            }
            if(passenger.allotted_elevator!=-1)     //Elevator has been allotted to passenger, no need to search idle elevators
                continue;

            int max_distance = INT_MAX;
            int best_elevator = -1;
            for(const auto &j:idle_elevators)
            {
                if(std::abs(elevators[j].floor - passenger.start_floor)<max_distance)
                {
                    best_elevator = j;
                    max_distance = std::abs(elevators[j].floor - passenger.start_floor);
                }
            }
            if(best_elevator!=-1)
            {
                passenger.allotted_elevator=best_elevator;
                elevators[best_elevator].direction = passenger.start_floor>elevators[best_elevator].floor ? UP : DOWN;
                elevators[best_elevator].assigned_pcount++;
                elevators[best_elevator].assigned_pdirn = passenger.direction;
                active_elevators.push_back(best_elevator);
                idle_elevators.erase(std::remove(idle_elevators.begin(), idle_elevators.end(), best_elevator), idle_elevators.end());
                std::cout<<"Allocating elevator to passenger. Passenger details are as follows "<<std::endl;
                passenger.compact_print();
            }
        }

        //Implement elevator fill logic!
        for(int i=0;i<active_total_passengers.size();i++)
        {
            if(active_total_passengers[i].board_start_time==-1)  //Passenger hasn't boarded the elevator yet
            {
                if(elevators[active_total_passengers[i].allotted_elevator].num_people()==MAX_CAPACITY)
                    //For the case when this passenger was allocated the elevator, but it got filled even before it reached this passenger
                {
                    deallocate_passenger_from_elevator(active_total_passengers[i],elevators[active_total_passengers[i].allotted_elevator]);
                }


                if(elevators[active_total_passengers[i].allotted_elevator].floor == active_total_passengers[i].start_floor) //Elevator has reached passenger floor
                {
                    std::cout<<"Elevator has reached passenger"<<std::endl;
                    active_total_passengers[i].compact_print();
                    elevators[active_total_passengers[i].allotted_elevator].elevator_status = BOARDING;
                    active_total_passengers[i].board_start_time = PRESENT_TIME;
                }
            }
            else
            {
                if(elevators[active_total_passengers[i].allotted_elevator].num_people()==MAX_CAPACITY)
                //For the case when two or more passengers want to enter at the same floor but the lift doesn't have that much capacity
                {
                    deallocate_passenger_from_elevator(active_total_passengers[i],elevators[active_total_passengers[i].allotted_elevator]);
                }

                else if(PRESENT_TIME - active_total_passengers[i].board_start_time == PDO_TIME)   //It's time for passenger to board;
                {
                    auto boarding_passenger = active_total_passengers[i];
                    auto elevator_index = boarding_passenger.allotted_elevator;
                    std::cout<<"Boarded Passenger.. "<<std::endl;
                    boarding_passenger.compact_print();
                    active_total_passengers.erase(active_total_passengers.begin()+i);
                    elevators[elevator_index].elevator_status = NONE;
                    elevators[elevator_index].pq.push(std::move(boarding_passenger));
                    elevators[elevator_index].reduce_pcount();
                    if(elevators[elevator_index].assigned_pcount==0 || elevators[elevator_index].num_people()==MAX_CAPACITY)    //If there is no one else more to pick or if the elevator has reached it's max capacity. It should start dropping people
                    {
                        elevators[elevator_index].direction = boarding_passenger.direction;
                        for(int k=0;k<active_total_passengers.size();k++)
                        {
                            if(active_total_passengers[k].allotted_elevator==elevator_index)
                                deallocate_passenger_from_elevator(active_total_passengers[k],elevators[elevator_index]);
                        }
                    }

                }
            }
        }
        PRESENT_TIME++;
    }

    cout<<"====================   RESULT   ========================================="<<endl;

    for(int  i=0;i<dropped_passengers.size();i++)
    {
        cout<<"Passenger: "<<i<<endl;
        cout<<"Passenger end time is: "<<dropped_passengers[i].end_time<<endl;
    }


    return 0;
}