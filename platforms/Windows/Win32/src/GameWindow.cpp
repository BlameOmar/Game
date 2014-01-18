#include "GameWindow.h"

#include "MessageQueue.h"
#include "Message.h"

#include <iostream>

namespace evansbros {
	namespace WindowsGUI {

		GameWindow::GameWindow(string title, unsigned int width, unsigned int height) : OpenGLWindow(title, width, height)
		{
			/* Intentionally Left Blank */
		}

		game::MessageQueue * GameWindow::getGameSystemMessageQueue()
		{
			return gameSystemMessageQueue;
		}

		graphics::WGLRenderer * GameWindow::getRenderer()
		{
			return renderer;
		}

		void GameWindow::setRenderer(graphics::WGLRenderer * renderer)
		{
			this->renderer = renderer;
			renderer->setNativeGraphicsContext(openGLContext);
			openGLContext->makeNotCurrent();
		}

		void GameWindow::setGameSystemMessageQueue(game::MessageQueue *messageQueue)
		{
			gameSystemMessageQueue = messageQueue;
		}

		void GameWindow::draw()
		{
			if (!renderer) {
				openGLContext->makeCurrent();

				glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				openGLContext->flush();
			}
		}

		void GameWindow::reshape(unsigned int width, unsigned int height)
		{
			if (!renderer) {
				glViewport(0, 0, width, height);
				return;
			}
			using namespace evansbros::game;
			gameSystemMessageQueue->enqueue(Message(ViewportEventType::RESIZE, { width, height }));
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
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_PAUSE));
				break;
			case 'W':
			case VK_UP:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_UP));
				break;
			case 'A':
			case VK_LEFT:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_LEFT));
				break;
			case 'S':
			case VK_DOWN:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_DOWN));
				break;
			case 'D':
			case VK_RIGHT:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_RIGHT));
				break;
				/* Player 2*/
			case 'P':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_PAUSE));
				break;
			case 'I':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_UP));
				break;
			case 'J':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_LEFT));
				break;
			case 'K':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_DOWN));
				break;
			case 'L':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_RIGHT));
				break;
			}
		}

		void GameWindow::keyUp(WPARAM keyCode)
		{
			using namespace evansbros::game;

			switch (keyCode) {
				/* Player 1*/
			case VK_ESCAPE:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_PAUSE));
				break;
			case 'W':
			case VK_UP:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_UP));
				break;
			case 'A':
			case VK_LEFT:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_LEFT));
				break;
			case 'S':
			case VK_DOWN:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_DOWN));
				break;
			case 'D':
			case VK_RIGHT:
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_RIGHT));
				break;
				/* Player 2*/
			case 'P':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_PAUSE));
				break;
			case 'I':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_UP));
				break;
			case 'J':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_LEFT));
				break;
			case 'K':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_DOWN));
				break;
			case 'L':
				gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_RIGHT));
				break;
			}
		}
	}
}