#pragma once

#include "Window.h"
#include "WGLContextObj.h"

namespace evansbros {
	namespace WindowsGUI {

		class WGLContextObj;

		class OpenGLWindow : public Window {
		protected:
			WGLContextObj *openGLContext;

			virtual void setupGL();
			virtual void reshape(unsigned int width, unsigned int height);

		public:
			OpenGLWindow(string title, unsigned int width, unsigned int height);
			OpenGLWindow(const OpenGLWindow & other) = delete;
			~OpenGLWindow();

			virtual void draw();

			void close();
		};
	}
}