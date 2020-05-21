//
// Created by Harsh Sharma on 19/05/20.
//

#pragma once

#include "input.h"
#include <iostream>

class Passenger {
public:
    int start_time;
    int start_floor;
    int end_floor;
    int board_start_time;   //Absolute board_start Time
    int dropoff_start_time; //Absolute dropoff_start Time
    int end_time;           //Absolute End Time
    int allotted_elevator;
    DIRN direction;

    Passenger(int new_start_time,int new_start_floor, int new_end_floor, int new_board_start_time,int new_dropoff_start_time,int new_end_time,int new_allotted_elv, DIRN new_direction):
    start_time(new_start_time), start_floor(new_start_floor), end_floor(new_end_floor), board_start_time(new_board_start_time), dropoff_start_time(new_dropoff_start_time),end_time(new_end_time), allotted_elevator(new_allotted_elv),direction(new_direction){}
    Passenger():Passenger(0,1,1,-1,-1,-1,-1,IDLE){}
    Passenger(int new_start_time,int new_start_floor, int new_end_floor): Passenger(new_start_time,new_start_floor,new_end_floor,-1,-1,-1,-1,IDLE) {}

    int get_total_time();
    void update_direction(DIRN new_direction);
    void compute_direction();
    void compact_print();
};

//=====================================================================================================================

struct Comp{
    bool operator()(const Passenger &a, const Passenger &b){

        assert(a.direction==b.direction);
        if(a.direction==UP)
            return a.end_floor>b.end_floor;
        else
            return a.end_floor<b.end_floor;
    }
};

//=====================================================================================================================



