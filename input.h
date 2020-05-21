//
// Created by Harsh Sharma on 19/05/20.
//

#pragma once

#include <vector>

const int NUM_FLOORS = 3;   //n
const int NUM_ELEVATORS = 2;    //m
const int TIME_TO_COVER_FLOOR = 1;   //x
const int PDO_TIME = 2;  //y
const int MAX_CAPACITY = 1; //z
const int NUM_PASSENGERS = 2;   //l
const std::vector<std::vector<int>> PASSENGERS{std::vector<int> {0,1,3},std::vector<int> {3,2,1}};  //input_array

enum DIRN{UP,DOWN,IDLE};
std::ostream& operator << (std::ostream& os, const DIRN& obj);

