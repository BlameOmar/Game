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
namespace evansbros {
	namespace game {

#if (!defined _MSC_VER || _MSC_VER > 1800)
		struct Point2D {
			real x = 0.0f;
			real y = 0.0f;

			Point2D() = default;
			Point2D(real x, real y) : x(x), y(y) {}
		};
#else
		struct Point2D {
			real x;
			real y;
		};
#endif

		enum class MessageType : natural {
			GENERIC,
			BUTTON,
			MOUSE
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
	}
}