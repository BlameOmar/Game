#pragma once

#include "OpenGLWindow.h"

namespace evansbros {
	namespace WindowsGUI {

		class GameWindow : public OpenGLWindow
		{
		protected:
			virtual void reshape(unsigned int width, unsigned int height);
			virtual void keyDown(WPARAM keyCode, bool isRepeat, unsigned short int repeatCount);
			virtual void keyUp(WPARAM keyCode);
		public:
			GameWindow(HINSTANCE instanceHandle, string title, unsigned int width, unsigned int height, PIXELFORMATDESCRIPTOR &pixelFormatDescriptor);
			
			virtual void draw();
		};

	}
}

