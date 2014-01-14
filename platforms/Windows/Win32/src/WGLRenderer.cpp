#include "WGLRenderer.h"

#include "WGLContextObj.h"

using evansbros::WindowsGUI::WGLContextObj;

namespace evansbros {
	namespace graphics {

		WGLContextObj * WGLRenderer::getNativeGraphicsContext()
		{
			return nativeGraphicsContext;
		}

		void WGLRenderer::setNativeGraphicsContext(WGLContextObj *context)
		{
			nativeGraphicsContext = context;
		}

		void WGLRenderer::setup()
		{
			nativeGraphicsContext->lock();
			nativeGraphicsContext->makeCurrent();

			if (gl3wInit()) {
				throw std::runtime_error("Failed to initialize OpenGL");
			}

			if (!gl3wIsSupported(3, 3)) {
				throw std::runtime_error("OpenGL 3.3 is not supported");
			}

			glDepthRange(1, 0);

			OpenGLRenderer::setup();

			nativeGraphicsContext->flush();

			nativeGraphicsContext->makeNotCurrent();
			nativeGraphicsContext->unlock();
		}

		void WGLRenderer::render(seconds interpolation)
		{
			nativeGraphicsContext->lock();
			nativeGraphicsContext->makeCurrent();

			OpenGLRenderer::render(interpolation);
			nativeGraphicsContext->flush();

			nativeGraphicsContext->makeNotCurrent();
			nativeGraphicsContext->unlock();
		}
	}
}