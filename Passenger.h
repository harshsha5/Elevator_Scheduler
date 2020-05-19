//
// Created by Harsh Sharma on 19/05/20.
//

#pragma once

#include "input.h"

class Passenger {
public:
    int start_time;
    int start_floor;
    int end_floor;
    int wait_time;
    int total_time;

    Passenger(int new_start_time,int new_start_floor, int new_end_floor, int new_wait_time,int new_total_time):
    start_time(new_start_time), start_floor(new_start_floor), end_floor(new_end_floor), wait_time(new_wait_time), total_time(new_total_time){}
    Passenger():Passenger(0,1,1,0,0){}
    Passenger(int new_start_time,int new_start_floor, int new_end_floor): Passenger(new_start_time,new_start_floor,new_end_floor,0,0) {}

    void update_total_time();
};



