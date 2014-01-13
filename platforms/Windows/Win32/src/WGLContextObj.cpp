#include "WGLContextObj.h"

#include <GL\glew.h>
#include <GL\wglew.h>

#include <stdexcept>

namespace evansbros {
	namespace WindowsGUI {

		WGLContextObj::WGLContextObj(HDC deviceContext)
			: deviceContext(deviceContext)
		{
			openGLContext = wglCreateContext(deviceContext);
			wglMakeCurrent(deviceContext, openGLContext);

			GLenum status = glewInit();
			if (status != GLEW_OK) {
				throw std::runtime_error((char *)glewGetErrorString(status));
			}

			if (wglewIsSupported("WGL_ARB_create_context") == 1) {
				HGLRC temp = openGLContext;
				int attributes[] {
					WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
					WGL_CONTEXT_MINOR_VERSION_ARB, 3,
					WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
					0
				};
				openGLContext = wglCreateContextAttribsARB(deviceContext, nullptr, attributes);
				wglMakeCurrent(deviceContext, openGLContext);
				wglDeleteContext(temp);
			}
		}

		WGLContextObj::~WGLContextObj()
		{
			lock();

			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(openGLContext);
			
			unlock();
		}

		void WGLContextObj::lock()
		{
			contextObjectMutex.lock();
		}

		void WGLContextObj::unlock()
		{
			contextObjectMutex.unlock();
		}

		void WGLContextObj::makeCurrent()
		{
			wglMakeCurrent(deviceContext, openGLContext);
		}

		void WGLContextObj::flush()
		{
			glFlush();
			SwapBuffers(deviceContext);
		}
	}
}