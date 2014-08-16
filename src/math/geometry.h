/**********************************************************************************************************************
 * @file    geometry.h
 * @date    2014-08-15
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#pragma once

#include "numerical_types.h"
#include "mathematical_constants.h"
#include "vector2.h"

namespace evansbros { namespace math { namespace geometry {

    struct LineSegment {
        vector2 midpoint;
        real length = 1.0/0.0;
        real angle = 0.0;
    };

    struct Circle {
        vector2 center;
        real radius = 0.5;

        Circle() = default;
        Circle(vector2 center, real radius) : center(center), radius(radius) { /* Nothing to do here */ }
    };

    bool areIntersecting(const Circle c1, const Circle c2);
    bool areIntersecting(const LineSegment l1, const LineSegment l2);

}}}
