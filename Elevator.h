//
// Created by Harsh Sharma on 19/05/20.
//

#pragma once

#include <queue>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Passenger.h"
#include "input.h"

enum STATUS{BOARDING,DROPOFF,NONE};
std::ostream& operator << (std::ostream& os, const STATUS& obj);

//=====================================================================================================================

class Elevator {

public:
    std::priority_queue<Passenger, std::vector<Passenger>, Comp> pq;
    int floor;
    DIRN direction;
    int assigned_pcount; //Number of people the elevator has been assigned to pickup in the future
    DIRN assigned_pdirn;    //Which directioned passengers to pick
    STATUS elevator_status;
    int time_since_start;   //Used for lift traversal. Set to zero as soon as boarding or dropoff gets finished.
    int dropoff_time;       //Relative dropoff_time. Set to 0 when dropoff starts

    Elevator(std::priority_queue<Passenger, std::vector<Passenger>, Comp> new_pq, int new_floor, DIRN new_direction, int new_assigned_pcount, DIRN new_assigned_pdirn, STATUS new_status,int new_time_since_start, int new_dropoff_time):
    pq(new_pq), floor(new_floor), direction(new_direction), assigned_pcount(new_assigned_pcount), assigned_pdirn(new_assigned_pdirn), elevator_status(new_status), time_since_start(new_time_since_start), dropoff_time(new_dropoff_time){}

    Elevator(int new_floor): floor(new_floor), direction(IDLE), assigned_pcount(0), assigned_pdirn(IDLE), elevator_status(NONE),time_since_start(-1),dropoff_time(-1){}

    std::vector<Passenger> step(int time);
    void update_floor();
    void set_idle();
    void post_drop_reset();
    void compact_print();
    void reduce_pcount();
    int num_people() { return pq.size(); }

};

//=====================================================================================================================

