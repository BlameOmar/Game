/**************************************************************************************************
 * Title:         MouseEvent.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "message_data_types.h"

namespace evansbros {
    namespace game {

        enum class MouseEventType : natural {
            MOUSE_MOVE
        };

#if (!defined _MSC_VER || _MSC_VER > 1800)
        struct MouseEvent {
            MouseEventType type;
            Point2D        location;

            MouseEvent(MouseEventType type, Point2D location) : type(type), location(location) {}
        };
#else
        struct MouseEvent {
            MouseEventType type;
            Point2D        location;
        };
#endif
        
    }
}