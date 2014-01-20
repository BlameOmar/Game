/**************************************************************************************************
 * Title:         ViewportEvent.h
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