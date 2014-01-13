//
//  Renderer.h
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/15/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#ifndef __OpenGL_Practice__Renderer__
#define __OpenGL_Practice__Renderer__

#include "GameState.h"

class Renderer {
private:
protected:
    const GameState *gameState;
public:
    virtual void setup() = 0;
    virtual void render() = 0;

    void setGameState(const GameState *gameState);
};

#endif /* defined(__OpenGL_Practice__Renderer__) */
