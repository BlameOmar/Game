//
//  OpenGLPracticeView.m
//  OpenGL Practice
//
//  Created by Omar Evans on 7/13/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#import "CGLRendererView.h"
#import <Carbon/Carbon.h>

using namespace evansbros;

@implementation CGLRendererView

-(evansbros::graphics::CGLRenderer *)renderer
{
    return _renderer;
}

- (void)setRenderer:(evansbros::graphics::CGLRenderer *)renderer
{
    _renderer = renderer;
    self.renderer->setNativeGraphicsContext((CGLContextObj)[self.openGLContext CGLContextObj]);
}

- (void)reshape
{
    CGLContextObj contextObj = (CGLContextObj)[self.openGLContext CGLContextObj];
    CGLLockContext(contextObj);

    if (self.renderer) {
        self.renderer->resizeViewport(self.bounds.size.width, self.bounds.size.height);
    } else {
        glViewport(0, 0, self.bounds.size.width, self.bounds.size.height);
    }

    CGLUnlockContext(contextObj);
}

- (void)update
{
    CGLContextObj contextObj = (CGLContextObj)[self.openGLContext CGLContextObj];
    CGLLockContext(contextObj);

    [super update];

    CGLUnlockContext(contextObj);
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGLContextObj contextObj = (CGLContextObj)[self.openGLContext CGLContextObj];
    CGLLockContext(contextObj);

    if (self.renderer) {
        self.renderer->render(seconds(0.0));
    } else {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        [self.openGLContext flushBuffer];
    }

    CGLUnlockContext(contextObj);
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyUp:(NSEvent *)theEvent
{
    using namespace evansbros::game;
    if (theEvent.isARepeat) {
        return;
    }

    switch (theEvent.keyCode) {
        /* Player 1*/
        case kVK_Escape:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_PAUSE));
            break;
        case kVK_ANSI_W:
        case kVK_UpArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_UP));
            break;
        case kVK_ANSI_A:
        case kVK_LeftArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_LEFT));
            break;
        case kVK_ANSI_S:
        case kVK_DownArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_DOWN));
            break;
        case kVK_ANSI_D:
        case kVK_RightArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P1_RIGHT));
            break;

        /* Player 2*/
        case kVK_ANSI_P:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_PAUSE));
            break;
        case kVK_ANSI_I:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_UP));
            break;
        case kVK_ANSI_J:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_LEFT));
            break;
        case kVK_ANSI_K:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_DOWN));
            break;
        case kVK_ANSI_L:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_RELEASE, ButtonID::P2_RIGHT));
            break;
    }
}

- (void)keyDown:(NSEvent *)theEvent
{
    using namespace evansbros::game;
    if (theEvent.isARepeat) {
        return;
    }

    switch (theEvent.keyCode) {
        /* Player 1 */
        case kVK_Escape:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_PAUSE));
            break;
        case kVK_ANSI_W:
        case kVK_UpArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_UP));
            break;
        case kVK_ANSI_A:
        case kVK_LeftArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_LEFT));
            break;
        case kVK_ANSI_S:
        case kVK_DownArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_DOWN));
            break;
        case kVK_ANSI_D:
        case kVK_RightArrow:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P1_RIGHT));
            break;

        /* Player 2*/
        case kVK_ANSI_P:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_PAUSE));
            break;
        case kVK_ANSI_I:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_UP));
            break;
        case kVK_ANSI_J:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_LEFT));
            break;
        case kVK_ANSI_K:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_DOWN));
            break;
        case kVK_ANSI_L:
            self.gameSystemMessageQueue->enqueue(Message(ButtonEventType::BUTTON_PRESS, ButtonID::P2_RIGHT));
            break;
    }
}

@end
