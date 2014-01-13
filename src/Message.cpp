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

#if (!defined _MSC_VER || _MSC_VER > 1800)
    Message::Message(ButtonEventType buttonEventType, ButtonID buttonID)
    : type(MessageType::BUTTON_EVENT), buttonEvent(buttonEventType, buttonID)
    {
        /* Intentionally Left Blank */
    }
#else
	Message::Message(ButtonEventType buttonEventType, ButtonID buttonID)
		: type(MessageType::BUTTON_EVENT)
	{
		buttonEvent.type = buttonEventType;
		buttonEvent.id = buttonID;
	}
#endif

#if (!defined _MSC_VER || _MSC_VER > 1800)
    Message::Message(MouseEventType mouseEventType, Point2D mouseLocation)
    : type(MessageType::MOUSE_EVENT), mouseEvent(mouseEventType, mouseLocation)
    {
        /* Intentionally Left Blank */
    }
#else
	Message::Message(MouseEventType mouseEventType, Point2D mouseLocation)
		: type(MessageType::MOUSE_EVENT)
	{
		mouseEvent.type = mouseEventType;
		mouseEvent.location = mouseLocation;
	}
#endif


    MessageType Message::getType() const
    {
        return type;
    }

    ButtonEvent Message::getButtonEvent() const {
        if (type != MessageType::BUTTON_EVENT) {
            throw MessageExceptions::InvalidOperation("This message is not a ButtonEvent");
        }
        return buttonEvent;
    }

    MouseEvent Message::getMouseEvent() const {
        if (type != MessageType::MOUSE_EVENT) {
            throw MessageExceptions::InvalidOperation("This message is not a MouseEvent");
        }
        return mouseEvent;
    }

} }
