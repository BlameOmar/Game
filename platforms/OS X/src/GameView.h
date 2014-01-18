//
//  OpenGLPracticeView.h
//  OpenGL Practice
//
//  Created by Omar Evans on 7/13/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//
#import <Cocoa/Cocoa.h>

#include "MessageQueue.h"
#include "CGLRenderer.h"

@interface GameView : NSOpenGLView {
    ::evansbros::graphics::CGLRenderer *_renderer;
    GLint swapInterval;
}

@property (assign) ::evansbros::game::MessageQueue *gameSystemMessageQueue;
@property (assign) ::evansbros::graphics::CGLRenderer *renderer;

@end
