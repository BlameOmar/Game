//
//  Event.cpp
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/12/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "Message.h"

namespace evansbros { namespace game {

    Message::Message()
    : type(MessageType::GENERIC_MESSAGE)
    {
        /* Intentionally Left Blank */
    }

    Message::Message(ButtonEventType buttonEventType, ButtonID buttonID)
    : type(MessageType::BUTTON_EVENT), buttonEvent(buttonEventType, buttonID)
    {
        /* Intentionally Left Blank */
    }

    Message::Message(MouseEventType mouseEventType, Point2D mouseLocation)
    : type(MessageType::MOUSE_EVENT), mouseEvent(mouseEventType, mouseLocation)
    {
        /* Intentionally Left Blank */
    }


    MessageType Message::getType() const
    {
        return type;
    }

    ButtonEvent Message::getButtonEvent() const throw(MessageExceptions::InvalidOperation) {
        if (type != MessageType::BUTTON_EVENT) {
            throw MessageExceptions::InvalidOperation("This message is not a ButtonEvent");
        }
        return buttonEvent;
    }

    MouseEvent Message::getMouseEvent() const throw(MessageExceptions::InvalidOperation) {
        if (type != MessageType::MOUSE_EVENT) {
            throw MessageExceptions::InvalidOperation("This message is not a MouseEvent");
        }
        return mouseEvent;
    }

} }
