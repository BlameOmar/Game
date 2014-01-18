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

#include "types.h"
#include "utilities.h"

#include "PixelData.h"

#include "MessageQueue.h"
#include "Message.h"

#include "GameController.h"
#include "GameState.h"

namespace evansbros { 
	namespace graphics {
		class Renderer;
	}
	namespace game {

	class MessageQueue;
	class Message;
	struct ButtonEvent;

    using graphics::Renderer;
    using graphics::TextureQuality;

    class GameSystem {
    public:
        /**
         * 
         */
        GameSystem();

        MessageQueue * getMessageQueue();
        Renderer * getRenderer();

        void start();
        void stop();
    private:
        const natural MAX_UPDATES_PER_CYCLE = 3;
        const natural TARGET_UPDATE_FREQUENCY = 30; // HERTZ
        const microseconds TARGET_UPDATE_PERIOD { 1000 * 1000 / TARGET_UPDATE_FREQUENCY };

        std::thread runloopThread;
        MessageQueue *messageQueue;

        GameState gameState;
        Renderer *renderer;

        time_point currentTime;
        time_point lastUpdate;

        seconds interpolation;

        GameController p1Controller;
        GameController p2Controller;

        bool running;
        bool paused;

        void handleMessage(Message message);

        void handleButtonEvent(ButtonEvent buttonEvent);
        void handleButtonPressEvent(ButtonEvent buttonEvent);
        void handleButtonReleaseEvent(ButtonEvent buttonEvent);

        void handleViewportEvent(ViewportEvent viewportEvent);

        void update(seconds dTime);
        void run();

        /******************************************************************************************
         *****                                 Asset Loading                                  *****
         ******************************************************************************************/

        std::map<string, PixelData> nHD_Textures;
        std::map<string, PixelData> qHD_Textures;
        std::map<string, PixelData>  HD_Textures;
        std::map<string, PixelData> FHD_Textures;
        std::map<string, PixelData> QHD_Textures;
        std::map<string, PixelData> UHD_Textures;

        std::map<TextureQuality, std::map<string, PixelData>> textures;

        void loadTextures();
        void loadTexture(string textureName);

    };

} }
