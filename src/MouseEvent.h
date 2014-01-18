//
//  MouseEvent.h
//  Game
//
//  Created by Omar Stefan Evans on 1/17/14.
//
//

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