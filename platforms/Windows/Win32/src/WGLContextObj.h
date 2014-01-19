#pragma once

#include <GL\gl3w.h>

typedef struct HDC__ *HDC;
typedef struct HWND__ *HWND;

namespace evansbros {
	namespace WindowsGUI {

		class WGLContextObj {
			HDC   deviceContext = nullptr;
			HGLRC openGLContext = nullptr;

		public:
			WGLContextObj(HDC deviceContext);
			WGLContextObj(const WGLContextObj & other) = delete;
			~WGLContextObj();

			void makeCurrent();
			void makeNotCurrent();
			void flush();

			HDC getDeviceContext();
			HGLRC getOpenGLContext();
			void setOpenGLContext(HGLRC context);
		};

	}
}