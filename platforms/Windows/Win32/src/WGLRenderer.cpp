#include "WGLRenderer.h"

#include "WGLContextObj.h"

using evansbros::WindowsGUI::WGLContextObj;

namespace evansbros {
	namespace graphics {

		WGLRenderer::WGLRenderer(WGLContextObj * context) : nativeGraphicsContext(context)
		{
			/* Intentionally Left Blank */
		}

		void WGLRenderer::init()
		{
			nativeGraphicsContext->makeCurrent();

			if (gl3wInit()) {
				throw std::runtime_error("Failed to initialize OpenGL");
			}

			if (!gl3wIsSupported(3, 3)) {
				throw std::runtime_error("OpenGL 3.3 is not supported");
			}
		}

		void WGLRenderer::render(seconds interpolation)
		{
			OpenGLRenderer::render(interpolation);
			nativeGraphicsContext->flush();
		}
	}
}