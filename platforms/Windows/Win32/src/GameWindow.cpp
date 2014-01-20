#include "GameWindow.h"

#include "MessageQueue.h"
#include "Message.h"

#include <iostream>

namespace evansbros {
	namespace WindowsGUI {

		GameWindow::GameWindow(string title, unsigned int width, unsigned int height) : OpenGLWindow(title, width, height)
		{
			openGLContext->makeCurrent();
			_renderer = new graphics::WGLRenderer(openGLContext);
			_messageQueue = new game::MessageQueue(100);
			openGLContext->makeNotCurrent();
		}

		game::MessageQueue * GameWindow::messageQueue()
		{
			return _messageQueue;
		}

		graphics::WGLRenderer * GameWindow::renderer()
		{
			return _renderer;
		}

		void GameWindow::reshape(unsigned int width, unsigned int height)
		{
			using namespace evansbros::game;
			_messageQueue->enqueue(Message(ViewportEventType::RESIZE, { width, height }));
		}

		void GameWindow::keyDown(WPARAM keyCode, bool isRepeat, unsigned short int repeatCount)
		{
			using namespace evansbros::game;

			if (isRepeat) {
				return;
			}

			switch (keyCode) {
				/* Player 1*/
			case VK_ESCAPE:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_PAUSE));
				break;
			case 'W':
			case VK_UP:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_UP));
				break;
			case 'A':
			case VK_LEFT:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_LEFT));
				break;
			case 'S':
			case VK_DOWN:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_DOWN));
				break;
			case 'D':
			case VK_RIGHT:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_RIGHT));
				break;
				/* Player 2*/
			case 'P':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_PAUSE));
				break;
			case 'I':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_UP));
				break;
			case 'J':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_LEFT));
				break;
			case 'K':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_DOWN));
				break;
			case 'L':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_RIGHT));
				break;
			}
		}

		void GameWindow::keyUp(WPARAM keyCode)
		{
			using namespace evansbros::game;

			switch (keyCode) {
				/* Player 1*/
			case VK_ESCAPE:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_PAUSE));
				break;
			case 'W':
			case VK_UP:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_UP));
				break;
			case 'A':
			case VK_LEFT:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_LEFT));
				break;
			case 'S':
			case VK_DOWN:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_DOWN));
				break;
			case 'D':
			case VK_RIGHT:
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_RIGHT));
				break;
				/* Player 2*/
			case 'P':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_PAUSE));
				break;
			case 'I':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_UP));
				break;
			case 'J':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_LEFT));
				break;
			case 'K':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_DOWN));
				break;
			case 'L':
				_messageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_RIGHT));
				break;
			}
		}
	}
}