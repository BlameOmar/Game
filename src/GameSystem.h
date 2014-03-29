/**************************************************************************************************
 * Title:         GameSystem.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-13
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include <map>
#include <thread>

#include "Renderer.h"
#include "MessageQueue.h"

#include "GameController.h"
#include "GameState.h"

#include "types.h"
#include "PixelData.h"

#include "utilities.h"

namespace evansbros {
	namespace game {

    using graphics::Renderer;
    using graphics::TextureQuality;

    class GameSystem {
    public:
        /**
         * Constructs the GameSystem with the given Renderer and MessageQueue
         */
        GameSystem(Renderer *renderer, MessageQueue * messageQueue);

        /**
         * Starts the game.
         */
        void start();

        /**
         * Stops the game.
         */
        void stop();
        void run();
        void initialize();
        void doCycle();

    private:
        const natural MAX_UPDATES_PER_CYCLE = 3;
        const natural TARGET_UPDATE_FREQUENCY = 20; // HERTZ
        const microseconds TARGET_UPDATE_PERIOD { 1000 * 1000 / TARGET_UPDATE_FREQUENCY };

        Renderer     *renderer     = nullptr;
        MessageQueue *messageQueue = nullptr;

        std::thread runloopThread;

        std::map<TextureQuality, std::map<string, PixelData>> textures;

        GameController p1Controller;
        GameController p2Controller;
        GameState gameState;

        time_point currentTime;
        time_point lastUpdate;

        seconds interpolation {0.0};

        bool running = false;
        bool paused = false;

        void update(seconds dTime);

        /******************************************************************************************
         *****                                Message Handling                                *****
         ******************************************************************************************/

        void handleMessage(Message message);

        void handleButtonEvent(ButtonEvent buttonEvent);
        void handleButtonPressEvent(ButtonEvent buttonEvent);
        void handleButtonReleaseEvent(ButtonEvent buttonEvent);

        void handleViewportEvent(ViewportEvent viewportEvent);


        /******************************************************************************************
         *****                                 Asset Loading                                  *****
         ******************************************************************************************/

        void loadTextures();
        void loadTexture(string textureName);

    };

} }
