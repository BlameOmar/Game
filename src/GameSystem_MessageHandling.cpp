/**************************************************************************************************
 * Title:         GameSystem_MessageHandling.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameSystem.h"
#include <iostream>

namespace evansbros { namespace game {

    void GameSystem::handleMessage(Message message)
    {
        switch (message.getType()) {
            case MessageType::BUTTON_EVENT:
                handleButtonEvent(message.getButtonEvent());
                break;

            default:
                ;
        }
    }

    void GameSystem::handleButtonEvent(ButtonEvent buttonEvent)
    {
        switch (buttonEvent.type) {
            case ButtonEventType::BUTTON_PRESS:
                handleButtonPressEvent(buttonEvent);
                break;
            case ButtonEventType::BUTTON_RELEASE:
                handleButtonReleaseEvent(buttonEvent);
                break;

            default:
                break;
        }
    }

    void GameSystem::handleButtonPressEvent(ButtonEvent buttonEvent)
    {
        switch (buttonEvent.id) {

                /* Player 1 */
            case ButtonID::P1_UP:
                p1Controller.pressUpButton();
                break;
            case ButtonID::P1_DOWN:
                p1Controller.pressDownButton();
                break;
            case ButtonID::P1_LEFT:
                p1Controller.pressLeftButton();
                break;
            case ButtonID::P1_RIGHT:
                p1Controller.pressRightButton();
                break;
            case ButtonID::P1_PAUSE:
                std::cout << "PAUSE PRESSED\n";
                paused = !paused;
                break;

                /* Player 2 */
            case ButtonID::P2_UP:
                p2Controller.pressUpButton();
                break;
            case ButtonID::P2_DOWN:
                p2Controller.pressDownButton();
                break;
            case ButtonID::P2_LEFT:
                p2Controller.pressLeftButton();
                break;
            case ButtonID::P2_RIGHT:
                p2Controller.pressRightButton();
                break;
            case ButtonID::P2_PAUSE:
                std::cout << "PAUSE PRESSED\n";
                paused = !paused;
                break;


            default:
                std::cout << "SOME UNHANDLED BUTTON WAS PRESSED\n";
        }
    }

    void GameSystem::handleButtonReleaseEvent(ButtonEvent buttonEvent)
    {
        switch (buttonEvent.id) {

                /* Player 1 */
            case ButtonID::P1_UP:
                p1Controller.releaseUpButton();
                break;
            case ButtonID::P1_DOWN:
                p1Controller.releaseDownButton();
                break;
            case ButtonID::P1_LEFT:
                p1Controller.releaseLeftButton();
                break;
            case ButtonID::P1_RIGHT:
                p1Controller.releaseRightButton();
                break;
            case ButtonID::P1_PAUSE:
                std::cout << "PAUSE RELEASED\n";
                break;

                /* Player 2 */
            case ButtonID::P2_UP:
                p2Controller.releaseUpButton();
                break;
            case ButtonID::P2_DOWN:
                p2Controller.releaseDownButton();
                break;
            case ButtonID::P2_LEFT:
                p2Controller.releaseLeftButton();
                break;
            case ButtonID::P2_RIGHT:
                p2Controller.releaseRightButton();
                break;
            case ButtonID::P2_PAUSE:
                std::cout << "PAUSE RELEASED\n";
                break;


            default:
                std::cout << "SOME UNHANDLED BUTTON WAS RELEASED\n";
        }
    }

} }
