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

	/**
	 * TODO: MSVC12's standard library has a non-conformant implementation of std::chrono::steady_clock
	 * It uses an imprecise duration and tracks the system time, which is affected by changes to/from
	 * Daylight Savings Time.  For now, we shall use this crappy clock. However, we must provide an
     * actual steady clock, preferably with nanosecond precission, for stability until/unless the bug
     * is fixed in a future standard library update.
	 */
	using microseconds = std::chrono::microseconds;
    using seconds     = std::chrono::duration<real_64bit>;
    using Clock       = std::chrono::steady_clock;
	using time_point  = Clock::time_point;
    
}
