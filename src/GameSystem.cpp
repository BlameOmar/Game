/**************************************************************************************************
 * Title:         GameSystem.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-13
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameSystem.h"

#include <iostream>
#include <numeric>

#include "mathematical_constants.h"

namespace evansbros {
    namespace game {

        using graphics::Renderer;

        GameSystem::GameSystem(Renderer *renderer, MessageQueue * messageQueue)
        : renderer(renderer), messageQueue(messageQueue)
        {
            if (!renderer) {
                throw std::runtime_error("Renderer pointer must not be nullptr.");
            }
            if (!messageQueue) {
                throw std::runtime_error("MessageQueue pointer must not be nullptr.");
            }

            renderer->setGameState(&gameState);
            renderer->setTextures(&textures);
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
        {
            initialize();
            while (running) {
                doCycle();
                std::this_thread::yield();
            }
        }

        void GameSystem::initialize() {
            renderer->init();
            loadTextures();
            renderer->loadGPU_Textures();

            gameState.player1 = gameState.createHuman({0.0, 0.0});
            gameState.player2 = gameState.createHuman({0.0, 0.0});
            gameState.camera = gameState.createCamera({0.0, 0.0});

            currentTime = Clock::now();
            lastUpdate = currentTime;
        }

        void GameSystem::doCycle() {
            currentTime = Clock::now();

            while (!messageQueue->wasEmpty()) {
                handleMessage(messageQueue->dequeue());
            }

            natural numberOfUpdates = 0;
            while (currentTime - lastUpdate > TARGET_UPDATE_PERIOD && numberOfUpdates < MAX_UPDATES_PER_CYCLE) {
                update(TARGET_UPDATE_PERIOD);
                lastUpdate += TARGET_UPDATE_PERIOD;
                ++numberOfUpdates;
            }

            if (numberOfUpdates > 1) {
                std::cout << numberOfUpdates - 1 << "frame(s) skipped!\n";
            }

            if (!paused) {
                interpolation = currentTime - lastUpdate;
            }

            renderer->render(interpolation);
        }

        void GameSystem::update(seconds dTime) {
            if (paused) {
                return;
            }

            gameState.updateSpatialComponents(dTime);

            math::vector2 movementDelta;

            /* Player 1 */
            SpatialComponent &p1SpatialComponent = gameState.getSpatialComponentWithEntityID(gameState.player1);

            if (p1Controller.upButtonIsPressed() && p1Controller.leftButtonIsPressed()) {
                movementDelta = math::vector2{-math::SQRT_2 / 2, math::SQRT_2 / 2};
            } else if (p1Controller.upButtonIsPressed() && p1Controller.rightButtonIsPressed()) {
                movementDelta = math::vector2{math::SQRT_2 / 2, math::SQRT_2 / 2};
            } else if (p1Controller.downButtonIsPressed() && p1Controller.leftButtonIsPressed()) {
                movementDelta = math::vector2{-math::SQRT_2 / 2, -math::SQRT_2 / 2};
            } else if (p1Controller.downButtonIsPressed() && p1Controller.rightButtonIsPressed()) {
                movementDelta = math::vector2{math::SQRT_2 / 2, -math::SQRT_2 / 2};
            } else if (p1Controller.upButtonIsPressed()) {
                movementDelta = math::vector2{0, 1};
            } else if (p1Controller.downButtonIsPressed()) {
                movementDelta = math::vector2{0, -1};
            } else if (p1Controller.leftButtonIsPressed()) {
                movementDelta = math::vector2{-1, 0};
            } else if (p1Controller.rightButtonIsPressed()) {
                movementDelta = math::vector2{1, 0};
            } else if (p1SpatialComponent.speed() > 0.0) {
                movementDelta = -0.5 * ( p1SpatialComponent.velocity / p1SpatialComponent.speed() );
            }

            p1SpatialComponent.velocity += movementDelta;
            if (p1SpatialComponent.speed() > 4) {
                p1SpatialComponent.velocity = 4 * p1SpatialComponent.velocity / p1SpatialComponent.speed();
            }

            /* Player 2 */
            movementDelta = math::vector2{0.0, 0.0};
            SpatialComponent &p2SpatialComponent = gameState.getSpatialComponentWithEntityID(gameState.player2);

            if (p2Controller.upButtonIsPressed() && p2Controller.leftButtonIsPressed()) {
                movementDelta = math::vector2{-math::SQRT_2 / 2, math::SQRT_2 / 2};
            } else if (p2Controller.upButtonIsPressed() && p2Controller.rightButtonIsPressed()) {
                movementDelta = math::vector2{math::SQRT_2 / 2, math::SQRT_2 / 2};
            } else if (p2Controller.downButtonIsPressed() && p2Controller.leftButtonIsPressed()) {
                movementDelta = math::vector2{-math::SQRT_2 / 2, -math::SQRT_2 / 2};
            } else if (p2Controller.downButtonIsPressed() && p2Controller.rightButtonIsPressed()) {
                movementDelta = math::vector2{math::SQRT_2 / 2, -math::SQRT_2 / 2};
            } else if (p2Controller.upButtonIsPressed()) {
                movementDelta = math::vector2{0, 1};
            } else if (p2Controller.downButtonIsPressed()) {
                movementDelta = math::vector2{0, -1};
            } else if (p2Controller.leftButtonIsPressed()) {
                movementDelta = math::vector2{-1, 0};
            } else if (p2Controller.rightButtonIsPressed()) {
                movementDelta = math::vector2{1, 0};
            } else if (p2SpatialComponent.speed() > 0.0) {
                movementDelta = -0.5 * ( p2SpatialComponent.velocity / p2SpatialComponent.speed() );
                ;
            }

            p2SpatialComponent.velocity += movementDelta;
            if (p2SpatialComponent.speed() > 4) {
                p2SpatialComponent.velocity = 4 * p2SpatialComponent.velocity / p2SpatialComponent.speed();
            }

            SpatialComponent &cameraSpatialComponent = gameState.getSpatialComponentWithEntityID(gameState.camera);
            cameraSpatialComponent.position = (p1SpatialComponent.position + p2SpatialComponent.position) / 2;
            cameraSpatialComponent.velocity = (p1SpatialComponent.velocity + p2SpatialComponent.velocity) / 2;
        }
        
    }
}
