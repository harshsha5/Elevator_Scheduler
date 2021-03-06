//
// Created by Harsh Sharma on 19/05/20.
//

#include "Elevator.h"


void Elevator::update_floor()
{
    if(direction==UP && floor!=NUM_FLOORS)
        floor++;
    else if(direction==UP && floor==NUM_FLOORS)
        std::cout<<"Can't move up. Have already reached top floor"<<std::endl;
    else if(direction==DOWN  && floor!=1)
        floor--;
    else if(direction==DOWN  && floor==1)
        std::cout<<"Can't move down. Have already reached lowest floor"<<std::endl;
}

//=====================================================================================================================

void Elevator::set_idle()
{
    direction = IDLE;
    assigned_pdirn = IDLE;
    elevator_status = NONE;
}

//=====================================================================================================================

void Elevator::post_drop_reset()
{
    dropoff_time=-1;
    elevator_status = NONE;
    time_since_start=0;
    std::cout<<"Post Drop Reset Triggered"<<std::endl;
}

//=====================================================================================================================

void Elevator::reduce_pcount()
{
    assigned_pcount--;
    if(assigned_pcount<0)
    {
        std::cout<<"assigned_pcount  has fallen below 0. It is an ERROR!!"<<std::endl;
        exit (0);
    }
}

//=====================================================================================================================

void Elevator::compact_print()
{
    std::cout<<"At floor: "<<floor<<"\t"<<"Moving in direction: "<<direction<<std::endl;
    std::cout<<"Num passengers: "<<num_people()<<"\t"<<"Elevator Status: "<<elevator_status<<std::endl;
    std::cout<<"Assigned p_count: "<<assigned_pcount<<std::endl;
    std::cout<<"================================================================"<<std::endl;
}

//=====================================================================================================================

std::ostream& operator << (std::ostream& os, const STATUS& obj)
{
    switch(obj){
        case BOARDING:
            os<<"BOARDING";
            break;
        case DROPOFF:
            os<<"DROPOFF";
            break;
        case NONE:
            os<<"NONE";
            break;
        default:
            os<<"HELLA";
    }
    return os;
}