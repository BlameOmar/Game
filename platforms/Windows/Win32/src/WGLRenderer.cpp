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

			OpenGLRenderer::setup();

			nativeGraphicsContext->flush();
			nativeGraphicsContext->unlock();
		}

		void WGLRenderer::render(seconds interpolation)
		{
			nativeGraphicsContext->lock();
			nativeGraphicsContext->makeCurrent();

			OpenGLRenderer::render(interpolation);

			nativeGraphicsContext->flush();
			nativeGraphicsContext->unlock();
		}
	}
}