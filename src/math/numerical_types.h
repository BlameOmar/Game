/**************************************************************************************************
 * Title:         numerical_types.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-06
 * Description:   Aliases for numerical types
 * Purpose:       To have nice names for numerical types
 * Modifications: None
 **************************************************************************************************/

#pragma once

#include <cstddef>
#include <cstdint>

namespace evansbros {

    using integer_8bit      = int8_t;
    using integer_16bit     = int16_t;
    using integer_32bit     = int32_t;
//    using integer_64bit     = int64_t;

    using natural_8bit      = uint8_t;
    using natural_16bit     = uint16_t;
    using natural_32bit     = uint32_t;
//    using natural_64bit     = uint64_t;

    

    using real_32bit        = float;
    using real_64bit        = double;

    using byte              = natural_8bit;
    using natural           = natural_32bit;
    using integer           = integer_32bit;
    using real              = real_32bit;

    using Index             = uintptr_t;

    const size_t minimumSize  = 0;
    const size_t maximumSize  = SIZE_MAX;

    using ID                = natural;
    using UniqueID          = natural;

}
