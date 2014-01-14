#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <Windows.h>

using string = std::string;

namespace evansbros {
	namespace WindowsGUI {

		class Window {
			string title;
			unsigned int width;
			unsigned int height;

			const static wchar_t CLASS_NAME[7];
			static std::unordered_map<HWND, Window *> windows;

			static bool wasRegistered;
			static void Register();
		protected:
			HWND windowHandle;
			HDC deviceContext;
		public:
			Window(string title, unsigned int width, unsigned int height);
			Window(const Window & other) = delete;
			~Window();

			static Window * getWindow(HWND windowHandle);
			static size_t count();

			virtual void draw();
			virtual void close();
			virtual void keyDown(size_t keycode, bool isRepeat, unsigned short int repeatCount);
			virtual void keyUp(size_t keycode);
			virtual void reshape(unsigned int width, unsigned int height);

			void display();
			void update();
			void resize(unsigned int width, unsigned int height);
		};
	}
}