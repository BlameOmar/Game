#include "GameWindow.h"

#include <iostream>

namespace evansbros {
	namespace WindowsGUI {

		GameWindow::GameWindow(HINSTANCE instanceHandle, string title, unsigned int width, unsigned int height, PIXELFORMATDESCRIPTOR &pixelFormatDescriptor)
			: OpenGLWindow(instanceHandle, title, width, height, pixelFormatDescriptor)
		{
			/* Intentionally Left Blank */
		}

		void GameWindow::draw()
		{
			openGLContext->lock();


			openGLContext->makeCurrent();

			glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			openGLContext->flush();


			openGLContext->unlock();
		}

		void GameWindow::reshape(unsigned int width, unsigned int height)
		{
			openGLContext->lock();


			openGLContext->makeCurrent();

			glViewport(0, 0, width, height);


			openGLContext->unlock();
		}

		void GameWindow::keyDown(WPARAM keyCode, bool isRepeat, unsigned short int repeatCount)
		{
			if (isRepeat) {
				return;
			}

			switch (keyCode) {
				/* Player 1*/
			case VK_ESCAPE:
				std::cout << "Player 1 pressed the pause key\n";
				break;
			case 'W':
			case VK_UP:
				std::cout << "Player 1 pressed the up key\n";
				break;
			case 'A':
			case VK_LEFT:
				std::cout << "Player 1 pressed the left key\n";
				break;
			case 'S':
			case VK_DOWN:
				std::cout << "Player 1 pressed the down key\n";
				break;
			case 'D':
			case VK_RIGHT:
				std::cout << "Player 1 pressed the right key\n";
				break;
				/* Player 2*/
			case 'P':
				std::cout << "Player 2 pressed the pause key\n";
				break;
			case 'I':
				std::cout << "Player 2 pressed the up key\n";
				break;
			case 'J':
				std::cout << "Player 2 pressed the left key\n";
				break;
			case 'K':
				std::cout << "Player 2 pressed the down key\n";
				break;
			case 'L':
				std::cout << "Player 2 pressed the right key\n";
				break;
			}
		}

		void GameWindow::keyUp(WPARAM keyCode)
		{
			switch (keyCode) {
				/* Player 1*/
			case VK_ESCAPE:
				std::cout << "Player 1 released the pause key\n";
				break;
			case 'W':
			case VK_UP:
				std::cout << "Player 1 released the up key\n";
				break;
			case 'A':
			case VK_LEFT:
				std::cout << "Player 1 released the left key\n";
				break;
			case 'S':
			case VK_DOWN:
				std::cout << "Player 1 released the down key\n";
				break;
			case 'D':
			case VK_RIGHT:
				std::cout << "Player 1 released the right key\n";
				break;
				/* Player 2*/
			case 'P':
				std::cout << "Player 2 released the pause key\n";
				break;
			case 'I':
				std::cout << "Player 2 released the up key\n";
				break;
			case 'J':
				std::cout << "Player 2 released the left key\n";
				break;
			case 'K':
				std::cout << "Player 2 released the down key\n";
				break;
			case 'L':
				std::cout << "Player 2 released the right key\n";
				break;
			}
		}
	}
}