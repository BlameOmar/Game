#pragma once

#include "OpenGLRenderer.h"

/* Forward Declaration of evansbros::WindowsGUI::WGLContextObj */
namespace evansbros {
	namespace WindowsGUI {
		class WGLContextObj;
	}
}
using evansbros::WindowsGUI::WGLContextObj;

namespace evansbros {
	namespace graphics {

		class WGLRenderer : public OpenGLRenderer {
		public:
			WGLRenderer(WGLContextObj *context);

			void init();
			void render(seconds interpolation);
		private:
			WGLContextObj *nativeGraphicsContext = nullptr;
		};

	}
}