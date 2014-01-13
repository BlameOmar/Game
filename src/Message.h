//
//  Event.h
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/12/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#pragma once

#include "types.h"
#include "Data.h"
#include "ButtonEvent.h"

#include <stdexcept>
namespace evansbros { namespace game {
    struct Point2D {
        real x;
        real y;

        Point2D() : Point2D(0.0, 0.0) {}
        Point2D(real x, real y) : x(x), y(y) {}
    };

    enum class MessageType : natural {
        GENERIC_MESSAGE,
        GENERIC_EVENT,
        BUTTON_EVENT,
        MOUSE_EVENT
    };

    enum class MouseEventType : natural {
        MOUSE_MOVE
    };

    namespace MessageExceptions {
        class InvalidOperation : public std::runtime_error {
        public:
            InvalidOperation(string what) : std::runtime_error(what) {}
        };
    }

    struct MouseEvent {
        MouseEventType type;
        Point2D        location;

        MouseEvent(MouseEventType type, Point2D location) : type(type), location(location) {}
    };

    class Message {
        MessageType type;
        union {
            ButtonEvent buttonEvent;
            MouseEvent mouseEvent;
        };

    public:
        Message();
        Message(ButtonEventType buttonEventType, ButtonID buttonID);
        Message(MouseEventType mouseEventType, Point2D mouseLocation);
        Message(Data data);

        MessageType getType() const;
        ButtonEvent getButtonEvent() const;
        MouseEvent getMouseEvent() const;
    };

} }
