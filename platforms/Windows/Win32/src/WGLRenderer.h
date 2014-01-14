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
			WGLContextObj *getNativeGraphicsContext();
			void setNativeGraphicsContext(WGLContextObj *context);

			void setup();
			void render(seconds interpolation);
		private:
			WGLContextObj *nativeGraphicsContext = nullptr;
		};

	}
}