#pragma once

#include <Windows.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

using string = std::string;

namespace evansbros {
	namespace WindowsGUI {

		class Window {
			string title;
			unsigned int width;
			unsigned int height;

			const static wchar_t CLASS_NAME[7];
			static std::unordered_set<HINSTANCE> registeredInstances;

			static bool wasRegistered(HINSTANCE instanceHandle);
			static void Register(HINSTANCE instanceHandle);
			friend LRESULT CALLBACK WindowHandleMessage(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
		protected:
			HWND windowHandle;
			static std::unordered_map<HWND, Window *> windows;

			HDC deviceContext;

			virtual void keyDown(WPARAM keycode, bool isRepeat, unsigned short int repeatCount);
			virtual void keyUp(WPARAM keycode);
			virtual void reshape(unsigned int width, unsigned int height);
		public:
			Window(HINSTANCE instanceHandle, string title, unsigned int width, unsigned int height);
			Window(const Window & other) = delete;
			~Window();

			static Window * getWindow(HWND windowHandle);

			virtual void draw();
			virtual void close();

			void display();
			void update();
			void resize(unsigned int width, unsigned int height);
		};
	}
}