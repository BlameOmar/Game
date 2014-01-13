#pragma once

#include <Windows.h>
#include <mutex>

namespace evansbros {
	namespace WindowsGUI {

		class WGLContextObj
		{
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
			void flush();
		};

	}
}
