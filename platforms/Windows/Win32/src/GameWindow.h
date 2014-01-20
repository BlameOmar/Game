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

			game::MessageQueue * messageQueue();
			graphics::WGLRenderer * renderer();

		protected:
			virtual void reshape(unsigned int width, unsigned int height);
			virtual void keyDown(WPARAM keyCode, bool isRepeat, unsigned short int repeatCount);
			virtual void keyUp(WPARAM keyCode);

		private:
			graphics::WGLRenderer *_renderer = nullptr;
			game::MessageQueue    *_messageQueue = nullptr;
		};

	}
}

