/**********************************************************************************************************************
 * @file    geometry.cpp
 * @date    2014-08-15
 * @brief   <# Brief Description #>
 * @details <# Detailed Description #>
 **********************************************************************************************************************/

#include "geometry.h"
#include <cmath>

namespace evansbros { namespace math { namespace geometry {

    bool areIntersecting(const Circle c1, const Circle c2) {
        return (c1.center - c2.center).magnitude() <= (c1.radius + c2.radius);
    }

    bool areIntersecting(const LineSegment l1, const LineSegment l2) {
        const real epsilon = 0.0001;

        const real l1_slope = tan(l1.angle);
        const real l2_slope = tan(l2.angle);

        const real l1_y_intercept = -l1_slope * l1.midpoint.x + l1.midpoint.y;
        const real l2_y_intercept = -l2_slope * l2.midpoint.x + l2.midpoint.y;


        /* Check if they are parallel */
        if (fabs(l1.angle - l2.angle) < epsilon) {
            /* Check if they are colinear */
            if (fabs(l1_y_intercept - l2_y_intercept) < epsilon) {
                /* Check if the segments touch */
                if ((l1.midpoint - l2.midpoint).magnitude() <= 0.5 * (l1.length + l2.length)) {
                    return true;
                }
            }

            return false;
        }

        real x = (l1_y_intercept - l2_y_intercept) / (l2_slope - l1_slope);
        real y = l1_slope * x + l1_y_intercept;

        math::vector2 intersectionPoint { x, y };
        return ((l1.midpoint - intersectionPoint).magnitude() <= 0.5 * l1.length);
    }
    
}}}