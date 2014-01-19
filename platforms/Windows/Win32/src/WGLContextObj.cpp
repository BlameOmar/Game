#include "WGLContextObj.h"

#include <Windows.h>

#include <stdexcept>

namespace evansbros {
	namespace WindowsGUI {

		WGLContextObj::WGLContextObj(HDC deviceContext)
			: deviceContext(deviceContext)
		{
			openGLContext = wglCreateContext(deviceContext);
			wglMakeCurrent(deviceContext, openGLContext);
			
			if (gl3wInit()) {
				throw std::runtime_error("Failed to initialize OpenGL");
			}

			if (!gl3wIsSupported(3, 3)) {
				throw std::runtime_error("OpenGL 3.3 is not supported");
			}
		}

		WGLContextObj::~WGLContextObj()
		{
			makeNotCurrent();
			wglDeleteContext(openGLContext);
		}

		void WGLContextObj::makeCurrent()
		{
			wglMakeCurrent(deviceContext, openGLContext);
		}

		void WGLContextObj::makeNotCurrent()
		{
			wglMakeCurrent(deviceContext, nullptr);
		}

		void WGLContextObj::flush()
		{
			SwapBuffers(deviceContext);
		}

		HDC WGLContextObj::getDeviceContext()
		{
			return deviceContext;
		}

		HGLRC WGLContextObj::getOpenGLContext()
		{
			return openGLContext;
		}
		void WGLContextObj::setOpenGLContext(HGLRC context)
		{
			openGLContext = context;
		}
	}
}