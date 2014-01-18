//
//  ViewportEvent.h
//  Game
//
//  Created by Omar Stefan Evans on 1/17/14.
//
//

#pragma once

#include "message_data_types.h"

namespace evansbros {
    namespace game {

        enum class ViewportEventType : natural {
            RESIZE
        };

#if (!defined _MSC_VER || _MSC_VER > 1800)
        struct ViewportEvent {
            ViewportEventType type;
            Size2D            size;

            ViewportEvent(ViewportEventType type, Size2D size) : type(type), size(size) {}
        };
#else
        struct ViewportEvent {
            ViewportEventType type;
            Size2D            size;
        };
#endif
        
    }
}