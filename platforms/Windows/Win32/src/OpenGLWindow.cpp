#include "OpenGLWindow.h"

#include <stdexcept>

namespace evansbros {
	namespace WindowsGUI {

		OpenGLWindow::OpenGLWindow(string title, unsigned int width, unsigned int height) try : Window(title, width, height)
		{
			PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
			ZeroMemory(&pixelFormatDescriptor, sizeof(pixelFormatDescriptor));
			pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pixelFormatDescriptor.nVersion = 1;
			pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
			pixelFormatDescriptor.cColorBits = 32;
			pixelFormatDescriptor.cDepthBits = 24;
			pixelFormatDescriptor.cStencilBits = 8;

			int pixelFormatIndex = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);
			SetPixelFormat(deviceContext, pixelFormatIndex, &pixelFormatDescriptor);

			openGLContext = new WGLContextObj (deviceContext);

			setupGL();
		}
		catch (std::runtime_error error) {
			MessageBoxA(0, error.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
			PostQuitMessage(-1);
		}

		OpenGLWindow::~OpenGLWindow()
		{
			close();
		}

		/* Private member functions */

		void OpenGLWindow::setupGL()
		{
			/* Default Implementation Does Nothing */
		}

		void OpenGLWindow::draw()
		{
			openGLContext->makeCurrent();

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			openGLContext->flush();
		}

		void OpenGLWindow::reshape(unsigned int width, unsigned int height)
		{
			openGLContext->makeCurrent();

			glViewport(0, 0, width, height);
		}

		void OpenGLWindow::close()
		{
			delete openGLContext;
			openGLContext = nullptr;

			Window::close();
		}

	}
}