//
//  GameController.cpp
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/19/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "GameController.h"

namespace evansbros { namespace game {
    
    void GameController::Button::press()
    {
        pressed = true;
    }

    void GameController::Button::release()
    {
        pressed = false;
    }

    bool GameController::Button::isPressed()
    {
        return pressed;
    }

    void GameController::pressUpButton()
    {
        releaseDownButton();
        upButton.press();
    }

    void GameController::pressDownButton()
    {
        releaseUpButton();
        downButton.press();
    }

    void GameController::pressLeftButton()
    {
        releaseRightButton();
        leftButton.press();
    }

    void GameController::pressRightButton()
    {
        releaseLeftButton();
        rightButton.press();
    }

    void GameController::releaseUpButton()
    {
        upButton.release();
    }

    void GameController::releaseDownButton()
    {
        downButton.release();
    }

    void GameController::releaseLeftButton()
    {
        leftButton.release();
    }

    void GameController::releaseRightButton()
    {
        rightButton.release();
    }

    bool GameController::upButtonIsPressed()
    {
        return upButton.isPressed();
    }

    bool GameController::downButtonIsPressed()
    {
        return downButton.isPressed();
    }

    bool GameController::leftButtonIsPressed()
    {
        return leftButton.isPressed();
    }

    bool GameController::rightButtonIsPressed()
    {
        return rightButton.isPressed();
    }

} }
