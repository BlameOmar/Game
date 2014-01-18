//
//  ButtonEvent.h
//  Game
//
//  Created by Omar Stefan Evans on 12/15/13.
//
//

#pragma once

#include "message_data_types.h"

namespace evansbros {
    namespace game {
        enum class ButtonID : natural {
            MOUSE_LEFT              = 0x0000 | 0,
            MOUSE_RIGHT             = 0x0000 | 1,
            MOUSE_MIDDLE            = 0x0000 | 2,

            LEFT                    = 0x1000 | 0,
            RIGHT                   = 0x1000 | 1,
            UP                      = 0x1000 | 2,
            DOWN                    = 0x1000 | 3,
            ACTION                  = 0x1000 | 4,
            PRIMARY_ACTION          = 0x1000 | 4,
            CONFIRM                 = 0x1000 | 4,
            SECONDARY_ACTION        = 0x1000 | 5,
            BACK                    = 0x1000 | 5,
            START                   = 0x1000 | 6,
            PAUSE                   = 0x1000 | 6,

            P1_LEFT                 = 0x1000 | 0,
            P1_RIGHT                = 0x1000 | 1,
            P1_UP                   = 0x1000 | 2,
            P1_DOWN                 = 0x1000 | 3,
            P1_ACTION               = 0x1000 | 4,
            P1_PRIMARY_ACTION       = 0x1000 | 4,
            P1_CONFIRM              = 0x1000 | 4,
            P1_SECONDARY_ACTION     = 0x1000 | 5,
            P1_BACK                 = 0x1000 | 5,
            P1_START                = 0x1000 | 6,
            P1_PAUSE                = 0x1000 | 6,

            P2_LEFT                 = 0x2000 | 0,
            P2_RIGHT                = 0x2000 | 1,
            P2_UP                   = 0x2000 | 2,
            P2_DOWN                 = 0x2000 | 3,
            P2_ACTION               = 0x2000 | 4,
            P2_PRIMARY_ACTION       = 0x2000 | 4,
            P2_CONFIRM              = 0x2000 | 4,
            P2_SECONDARY_ACTION     = 0x2000 | 5,
            P2_BACK                 = 0x2000 | 5,
            P2_START                = 0x2000 | 6,
            P2_PAUSE                = 0x2000 | 6,

            P3_LEFT                 = 0x3000 | 0,
            P3_RIGHT                = 0x3000 | 1,
            P3_UP                   = 0x3000 | 2,
            P3_DOWN                 = 0x3000 | 3,
            P3_ACTION               = 0x3000 | 4,
            P3_PRIMARY_ACTION       = 0x3000 | 4,
            P3_CONFIRM              = 0x3000 | 4,
            P3_SECONDARY_ACTION     = 0x3000 | 5,
            P3_BACK                 = 0x3000 | 5,
            P3_START                = 0x3000 | 6,
            P3_PAUSE                = 0x3000 | 6,

            P4_LEFT                 = 0x4000 | 0,
            P4_RIGHT                = 0x4000 | 1,
            P4_UP                   = 0x4000 | 2,
            P4_DOWN                 = 0x4000 | 3,
            P4_ACTION               = 0x4000 | 4,
            P4_PRIMARY_ACTION       = 0x4000 | 4,
            P4_CONFIRM              = 0x4000 | 4,
            P4_SECONDARY_ACTION     = 0x4000 | 5,
            P4_BACK                 = 0x4000 | 5,
            P4_START                = 0x4000 | 6,
            P4_PAUSE                = 0x4000 | 6
        };

        enum class ButtonEventType : natural {
            BUTTON_PRESS,
            BUTTON_RELEASE
        };
        
#if (!defined _MSC_VER || _MSC_VER > 1800)
        struct ButtonEvent {
            ButtonEventType type;
            ButtonID        id;
            
            ButtonEvent(ButtonEventType type, ButtonID id) : type(type), id(id) {}
        };
#else
        struct ButtonEvent {
            ButtonEventType type;
            ButtonID        id;
        };
#endif
    }
}
