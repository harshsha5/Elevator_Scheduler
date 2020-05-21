//
// Created by Harsh Sharma on 19/05/20.
//

#include "Passenger.h"

int Passenger::get_total_time()
{
    return end_time - start_time;
}

//=====================================================================================================================

void Passenger::update_direction(DIRN new_direction)
{
    direction = new_direction;
}


//=====================================================================================================================

void Passenger::compute_direction()
{
    if(end_floor>start_floor)
        direction = UP;
    else
        direction = DOWN;
}

//=====================================================================================================================

void Passenger::compact_print()
{
    std::cout<<"Start time: "<<start_time<<"\t"<<"End Time: "<<end_time<<std::endl;
    std::cout<<"Start Floor: "<<start_floor<<"\t"<<"End Floor: "<<end_floor<<std::endl;
    std::cout<<"Allocated Elevator: "<<allotted_elevator<<std::endl;
    std::cout<<"================================================================"<<std::endl;
}

//=====================================================================================================================

std::ostream& operator << (std::ostream& os, const DIRN& obj)
{
    switch(obj){
        case UP:
            os<<"UP";
            break;
        case DOWN:
            os<<"DOWN";
            break;
        case IDLE:
            os<<"IDLE";
            break;
    }
    return os;
}