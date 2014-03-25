//
//  GameController.h
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/19/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#ifndef __OpenGL_Practice__GameController__
#define __OpenGL_Practice__GameController__

namespace evansbros { namespace game {

    class GameController {
    public:
        void pressUpButton();
        void pressDownButton();
        void pressLeftButton();
        void pressRightButton();

        void releaseUpButton();
        void releaseDownButton();
        void releaseLeftButton();
        void releaseRightButton();

        bool upButtonIsPressed();
        bool downButtonIsPressed();
        bool leftButtonIsPressed();
        bool rightButtonIsPressed();

        bool allDirectionalButtonsAreReleased();

    private:
        class Button {
        private:
            bool pressed = false;
        public:
            void press();
            void release();
            bool isPressed();
        };

        Button upButton;
        Button downButton;
        Button leftButton;
        Button rightButton;
    };

}}

#endif /* defined(__OpenGL_Practice__GameController__) */
