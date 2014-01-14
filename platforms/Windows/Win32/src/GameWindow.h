#pragma once

#include "OpenGLWindow.h"

#include "WGLRenderer.h"

// Forward Declarations
namespace evansbros {
	namespace game {
		class MessageQueue;
	}
}

namespace evansbros {
	namespace WindowsGUI {

		class GameWindow : public OpenGLWindow
		{
		public:
			GameWindow(string title, unsigned int width, unsigned int height);

			game::MessageQueue * getGameSystemMessageQueue();
			graphics::WGLRenderer * getRenderer();

			void setRenderer(graphics::WGLRenderer * renderer);
			void setGameSystemMessageQueue(game::MessageQueue *messageQueue);

			virtual void draw();

		protected:
			virtual void reshape(unsigned int width, unsigned int height);
			virtual void keyDown(WPARAM keyCode, bool isRepeat, unsigned short int repeatCount);
			virtual void keyUp(WPARAM keyCode);

		private:
			game::MessageQueue *gameSystemMessageQueue = nullptr;
			graphics::WGLRenderer *renderer = nullptr;
		};

	}
}

