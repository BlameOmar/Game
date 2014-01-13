/**************************************************************************************************
* Title:         main.cpp
* Author:        Omar Stefan Evans
* Created on:    2014-01-07
* Description:   <#Description#>
* Purpose:       <#Purpose#>
* Modifications: <#Modifications#>
**************************************************************************************************/

#include <Windows.h>

#ifdef _DEBUG
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#endif

#include "GameWindow.h"

using namespace evansbros::WindowsGUI;

int WindowsApplicationMain(int argc, wchar_t *argv[], HINSTANCE instanceHandle);

/**
 * Usually (w)WinMain is the entry point for graphical windows programs. We will not follow this
 * convention since nearly all of the parameters are no longer relevant to modern operating systems
 * and thus more confusing than useful. Instead, we will use wmain, which is similar to main, the
 * difference being that it accepts the command line arguments as wide-strings. This is necessary
 * because the Windows API does not support UTF-8, only UTF-16. Please set your linker setttings
 * appropriately. For MSVC, set /ENTRY to wmainCRTStartup and /SUBSYSTEM to WINDOWS.
 */
int wmain(int argc, wchar_t *argv[])
{
#ifdef _DEBUG
	AllocConsole();

	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((intptr_t)outputHandle, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;
	*stderr = *hf_out;

	std::ios::sync_with_stdio();

	int status =  WindowsApplicationMain(argc, argv, GetModuleHandleW(nullptr));

	FreeConsole();

	return status;
#else
	return WindowsApplicationMain(argc, argv, GetModuleHandleW(nullptr));
#endif
}

int WindowsApplicationMain(int argc, wchar_t *argv[], HINSTANCE instanceHandle)
{
	/* Create the main window */

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	ZeroMemory(&pixelFormatDescriptor, sizeof(pixelFormatDescriptor));
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 32;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cStencilBits = 8;

	Window *mainWindow = new GameWindow(instanceHandle, "Main Window", 640, 360, pixelFormatDescriptor);

	/* Display the main window */
	mainWindow->display();
	mainWindow->update();

	/* Enter message handling loop */
	MSG message;
	BOOL quitMessageNotReceived;
	while ((quitMessageNotReceived = GetMessageW(&message, nullptr, 0, 0)) != FALSE) {
		if (quitMessageNotReceived == -1) {
			MessageBoxW(nullptr, L"Something went horribly wrong", L"Error!", MB_ICONEXCLAMATION | MB_OK);
			exit(EXIT_FAILURE);
		}
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}

	/* Destroy the main window */
	delete mainWindow;

	return (int)message.wParam;
}