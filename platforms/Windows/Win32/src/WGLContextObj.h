#pragma once

#include <GL\gl3w.h>
#include <mutex>

typedef struct HDC__ *HDC;
typedef struct HWND__ *HWND;

namespace evansbros {
	namespace WindowsGUI {

		class WGLContextObj {
			HDC   deviceContext = nullptr;
			HGLRC openGLContext = nullptr;

			std::recursive_mutex contextObjectMutex;
		public:
			WGLContextObj(HDC deviceContext);
			WGLContextObj(const WGLContextObj & other) = delete;
			~WGLContextObj();

			void lock();
			void unlock();

			void makeCurrent();
			void makeNotCurrent();
			void flush();

			HDC getDeviceContext();

			HGLRC getOpenGLContext();
			void setOpenGLContext(HGLRC context);
		};

	}
}