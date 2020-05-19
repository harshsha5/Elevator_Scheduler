//
// Created by Harsh Sharma on 19/05/20.
//

#include "Passenger.h"

void Passenger::update_total_time()
{
    total_time = start_time + std::abs(end_floor-start_floor)*TIME_TO_COVER_FLOOR + 2*PDO_TIME + wait_time;
}

//=====================================================================================================================
