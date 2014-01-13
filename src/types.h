/**************************************************************************************************
 * Title:         types.h
 * Author:        Omar Stefan Evans
 * Created on:    <#Date#>
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"

#include <string>
#include <vector>
#include <chrono>

namespace evansbros {

    using string      = std::string;

//    template<typename T>
//    using array       = std::vector<T>;

    using nanoseconds = std::chrono::nanoseconds;
    using seconds     = std::chrono::duration<real>;
    using Clock       = std::chrono::steady_clock;
    using time_point  = std::chrono::time_point<Clock>;
    
}
