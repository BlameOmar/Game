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

#include "GameSystem.h"
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
try {
	/* Create the main window */
	GameWindow *mainWindow = new GameWindow("Main Window", 640, 360);

	/* Display the main window */
	mainWindow->display();
	mainWindow->update();

	game::GameSystem *gameSystem = new evansbros::game::GameSystem(mainWindow->renderer(), mainWindow->messageQueue());
	gameSystem->start();

	/* Enter message handling loop */
	MSG message;
	BOOL quitMessageNotReceived;
	while ((quitMessageNotReceived = GetMessageW(&message, nullptr, 0, 0)) != FALSE) {
		if (quitMessageNotReceived == -1) {
			MessageBoxW(nullptr, L"Something went horribly wrong", L"Error!", MB_ICONEXCLAMATION | MB_OK);
			break;
		}
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}

	gameSystem->stop();
	delete gameSystem;

	/* Destroy the main window */
	delete mainWindow;

	exit(EXIT_SUCCESS);
}
catch (std::runtime_error error) {
	MessageBoxA(0, error.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
	PostQuitMessage(-1);
}