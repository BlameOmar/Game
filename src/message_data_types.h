/**************************************************************************************************
 * Title:         message_data_types.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

namespace evansbros {
    namespace game {

#if (!defined _MSC_VER || _MSC_VER > 1800)
		struct Point2D {
			real x = 0.0f;
			real y = 0.0f;

			Point2D() = default;
			Point2D(real x, real y) : x(x), y(y) {}
		};

        struct Size2D {
            natural width = 0;
            natural height = 0;

            Size2D() = default;
            Size2D(natural width, natural height) : width(width), height(height) {}
        };
#else
		struct Point2D {
			real x;
			real y;
		};

        struct Size2D {
            natural width;
            natural height;
        };
#endif
        
    }
}