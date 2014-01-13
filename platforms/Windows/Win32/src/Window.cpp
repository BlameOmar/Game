#include "Window.h"

#include <codecvt>
#include <locale>
#include <stdexcept>

#include "resources\resource.h"

namespace evansbros {
	namespace WindowsGUI {
		/* Public member function definitions */
		Window::Window(HINSTANCE instanceHandle, string title, unsigned int width, unsigned int height)
			try : title(title), width(width), height(height)
		{
			if (!wasRegistered(instanceHandle)) {
				Register(instanceHandle);
			}

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring title_UTF16 = converter.from_bytes(title.c_str());

			windowHandle = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, CLASS_NAME, title_UTF16.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, instanceHandle, nullptr);
			if (!windowHandle) {
				throw std::runtime_error("Failed to create Window");
			}

			deviceContext = GetDC(windowHandle);

			windows[windowHandle] = this;
		}
		catch (std::runtime_error error) {
			MessageBoxA(0, error.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
			PostQuitMessage(-1);
		}

		Window::~Window()
		{
			close();
		}

		Window * Window::getWindow(HWND windowHandle)
		{
			return windows[windowHandle];
		}

		/* Private static variables */
		const wchar_t Window::CLASS_NAME[7] = L"Window";
		std::unordered_set<HINSTANCE> Window::registeredInstances;
		std::unordered_map<HWND, Window *> Window::windows;

		/* Private member functions */

		void Window::draw()
		{
			/* Default Implementation Does Nothing */
		}

		void Window::resize(unsigned int width, unsigned int height)
		{
			this->width = width;
			this->height = height;

			reshape(width, height);
		}

		void Window::keyDown(WPARAM keyCode, bool isRepeat, unsigned short int repeatCount)
		{
			/* Default Implementation Does Nothing */
		}

		void Window::keyUp(WPARAM keyCode)
		{
			/* Default Implementation Does Nothing */
		}

		void Window::reshape(unsigned int width, unsigned int height)
		{
			/* Default Implementation Does Nothing */
		}

		void Window::display()
		{
			ShowWindow(windowHandle, SW_SHOWDEFAULT);
		}

		void Window::update()
		{
			UpdateWindow(windowHandle);
		}

		void Window::close()
		{
			deviceContext = nullptr;

			windows.erase(windowHandle);
			DestroyWindow(windowHandle);
			windowHandle = nullptr;			
		}

		void Window::Register(HINSTANCE instanceHandle)
		try {
			WNDCLASSEXW windowClass;
			ZeroMemory(&windowClass, sizeof(windowClass));

			windowClass.cbSize = sizeof(WNDCLASSEXW);
			windowClass.style = CS_OWNDC;
			windowClass.lpfnWndProc = WindowHandleMessage;
			windowClass.hInstance = instanceHandle;
			windowClass.hIcon = LoadIconW(instanceHandle, MAKEINTRESOURCEW(IDI_ICON1));
			windowClass.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(IDI_APPLICATION));
			windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			windowClass.lpszMenuName = nullptr;
			windowClass.lpszClassName = CLASS_NAME;

			if (!RegisterClassExW(&windowClass)) {
				throw std::runtime_error("Registration of Window failed");
			}

			registeredInstances.insert(instanceHandle);
		} catch (std::runtime_error error) {
			MessageBoxA(0, error.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
			PostQuitMessage(-1);
		}

		bool Window::wasRegistered(HINSTANCE instanceHandle)
		{
			return registeredInstances.count(instanceHandle) != 0;
		}


		/* Private functions */


		LRESULT CALLBACK WindowHandleMessage(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message) {
			case WM_KEYDOWN:
				Window::windows[windowHandle]->keyDown(wParam, lParam >> 30 & 0x01, lParam & 0xFFFF);
				break;
			case WM_KEYUP:
				Window::windows[windowHandle]->keyUp(wParam);
				break;
			case WM_PAINT:
			case WM_ERASEBKGND:
				Window::windows[windowHandle]->draw();
				break;
			case WM_SIZE:
				Window::windows[windowHandle]->resize(LOWORD(lParam), HIWORD(lParam));
				Window::windows[windowHandle]->draw();
				break;
			case WM_CLOSE:
				Window::windows[windowHandle]->close();
				break;
			case WM_DESTROY:
				if (Window::windows.empty()) {
					PostQuitMessage(0);
				}
				break;
			default:
				return DefWindowProcW(windowHandle, message, wParam, lParam);
			}

			return 0;
		}

	}
}