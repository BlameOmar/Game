#pragma once

#include <Windows.h>
#include <GL\glew.h>
#include <GL\wglew.h>
#include <memory>

#include "Window.h"
#include "WGLContextObj.h"

namespace evansbros {
	namespace WindowsGUI {

		class OpenGLWindow : public Window {
		protected:
			WGLContextObj *openGLContext;

			virtual void setupGL();
			virtual void reshape(unsigned int width, unsigned int height);

		public:
			OpenGLWindow(HINSTANCE instanceHandle, string title, unsigned int width, unsigned int height, PIXELFORMATDESCRIPTOR &pixelFormatDescriptor);
			OpenGLWindow(const OpenGLWindow & other) = delete;
			~OpenGLWindow();

			virtual void draw();

			void close();
			void display();
			void update();
		};
	}
}