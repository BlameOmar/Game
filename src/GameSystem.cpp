/**************************************************************************************************
 * Title:         GameSystem.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-13
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameSystem.h"

#include "MessageQueue.h"
#include "Message.h"
#include "Renderer.h"

#include <iostream>
#include <thread>
#include <numeric>

#if TARGET_OS_OSX
    #include "CGLRenderer.h"
    typedef evansbros::CGLRenderer NativeRender;
#endif

#include "mathematical_constants.h"

namespace evansbros { namespace game {

    using graphics::Renderer;

    GameSystem::GameSystem() : running(false), paused(false)
    {
		messageQueue = new MessageQueue(100);
        renderer = getPlatformRenderer();
        renderer->setGameState(&gameState);
        renderer->setTextures(&textures);
    }

    MessageQueue * GameSystem::getMessageQueue()
    {
        return messageQueue;
    }

    Renderer * GameSystem::getRenderer()
    {
        return renderer;
    }

    void GameSystem::start()
    {
        std::cout << "Starting game!\n";
        running = true;
        runloopThread = std::thread(&GameSystem::run, this);
    }

    void GameSystem::stop()
    {
        std::cout << "Stopping game!\n";
        running = false;
        runloopThread.join();
    }

    void GameSystem::run()
    try {
        loadTextures();
        renderer->setup();

        currentTime = Clock::now();
        lastUpdate = currentTime;
        interpolation = seconds(0);

        time_point currentRender = currentTime;
        time_point lastRender = currentTime;


        const natural NUMBER_OF_SAMPLES = 256;
        seconds renderPeriods[NUMBER_OF_SAMPLES];
        natural renderPeriodIndex = 0;
        real fps;

        natural numberOfUpdates = 0;
        while (running) {
            currentTime = Clock::now();

            while (!messageQueue->wasEmpty()) {
                handleMessage(messageQueue->dequeue());
            }

            numberOfUpdates = 0;
            while (currentTime - lastUpdate > TARGET_UPDATE_PERIOD && numberOfUpdates < MAX_UPDATES_PER_CYCLE) {
                update(TARGET_UPDATE_PERIOD);
                lastUpdate += TARGET_UPDATE_PERIOD;
                ++numberOfUpdates;
            }

            if (numberOfUpdates > 1) {
                std::cout << "Frame skipped!\n";
            }

            if (!paused) {
                interpolation = Clock::now() - lastUpdate;
            }

            currentRender = Clock::now();
            renderPeriods[renderPeriodIndex] = currentRender - lastRender;
            renderPeriodIndex = (renderPeriodIndex + 1) % NUMBER_OF_SAMPLES;
            renderer->render(interpolation);
            lastRender = currentRender;

            if (renderPeriodIndex == NUMBER_OF_SAMPLES - 1) {
                fps = std::accumulate(renderPeriods, renderPeriods + NUMBER_OF_SAMPLES, seconds(0)).count() / NUMBER_OF_SAMPLES;
                std::cout << 1.0 / fps << " fps\n";
            }

            std::this_thread::yield();
        }
	}
	catch (std::runtime_error error) {
		std::cout << error.what() << std::endl;
		throw error;
	}



    void GameSystem::update(seconds dTime) {
        if (paused) {
            return;
        }

        math::vector3 movementDelta;

        /* Player 1 */
        if (p1Controller.upButtonIsPressed() && p1Controller.leftButtonIsPressed()) {
            movementDelta = math::vector3(-math::SQRT_2 / 2, math::SQRT_2 / 2);
        } else if (p1Controller.upButtonIsPressed() && p1Controller.rightButtonIsPressed()) {
            movementDelta = math::vector3(math::SQRT_2 / 2, math::SQRT_2 / 2);
        } else if (p1Controller.downButtonIsPressed() && p1Controller.leftButtonIsPressed()) {
            movementDelta = math::vector3(-math::SQRT_2 / 2, -math::SQRT_2 / 2);
        } else if (p1Controller.downButtonIsPressed() && p1Controller.rightButtonIsPressed()) {
            movementDelta = math::vector3(math::SQRT_2 / 2, -math::SQRT_2 / 2);
        } else if (p1Controller.upButtonIsPressed()) {
            movementDelta = math::vector3(0, 1);
        } else if (p1Controller.downButtonIsPressed()) {
            movementDelta = math::vector3(0, -1);
        } else if (p1Controller.leftButtonIsPressed()) {
            movementDelta = math::vector3(-1, 0);
        } else if (p1Controller.rightButtonIsPressed()) {
            movementDelta = math::vector3(1, 0);
        } else if (gameState.p1State.speed() > 0.0) {
            movementDelta = -0.5 * ( gameState.p1State.velocity / gameState.p1State.speed() );
        }

        gameState.p1State.incrementVelocity(movementDelta);

        if (gameState.p1State.speed() < 0.0625) {
            gameState.p1State.velocity = math::vector3(0.0, 0.0);
        }

        gameState.p1State.position += gameState.p1State.velocity * dTime.count();

        /* Player 2 */
        movementDelta = math::vector3(0.0, 0.0);

        if (p2Controller.upButtonIsPressed() && p2Controller.leftButtonIsPressed()) {
            movementDelta = math::vector3(-math::SQRT_2 / 2, math::SQRT_2 / 2);
        } else if (p2Controller.upButtonIsPressed() && p2Controller.rightButtonIsPressed()) {
            movementDelta = math::vector3(math::SQRT_2 / 2, math::SQRT_2 / 2);
        } else if (p2Controller.downButtonIsPressed() && p2Controller.leftButtonIsPressed()) {
            movementDelta = math::vector3(-math::SQRT_2 / 2, -math::SQRT_2 / 2);
        } else if (p2Controller.downButtonIsPressed() && p2Controller.rightButtonIsPressed()) {
            movementDelta = math::vector3(math::SQRT_2 / 2, -math::SQRT_2 / 2);
        } else if (p2Controller.upButtonIsPressed()) {
            movementDelta = math::vector3(0, 1);
        } else if (p2Controller.downButtonIsPressed()) {
            movementDelta = math::vector3(0, -1);
        } else if (p2Controller.leftButtonIsPressed()) {
            movementDelta = math::vector3(-1, 0);
        } else if (p2Controller.rightButtonIsPressed()) {
            movementDelta = math::vector3(1, 0);
        } else if (gameState.p2State.speed() > 0.0) {
            movementDelta = -0.5 * ( gameState.p2State.velocity / gameState.p2State.speed() );
        }

        gameState.p2State.incrementVelocity(movementDelta);

        if (gameState.p2State.speed() < 0.0625) {
            gameState.p2State.velocity = math::vector3(0.0, 0.0);
        }

        gameState.p2State.position += gameState.p2State.velocity * dTime.count();

        gameState.cameraState.position = (gameState.p1State.position + gameState.p2State.position) / 2;
        gameState.cameraState.velocity = (gameState.p1State.velocity + gameState.p2State.velocity) / 2;

    }

} }
