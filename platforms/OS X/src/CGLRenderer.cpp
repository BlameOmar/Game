//
//  CGLRenderer.cpp
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/15/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "CGLRenderer.h"

namespace evansbros { namespace graphics {

    CGLRenderer::CGLRenderer() {
    }

    CGLRenderer::~CGLRenderer() {
    }

    CGLContextObj CGLRenderer::getNativeGraphicsContext()
    {
        return nativeGraphicsContext;
    }

    void CGLRenderer::setNativeGraphicsContext(CGLContextObj context)
    {
        nativeGraphicsContext = context;
    }

    void CGLRenderer::setup()
    {
        CGLLockContext(nativeGraphicsContext);
        CGLSetCurrentContext(nativeGraphicsContext);

        OpenGlRenderer::setup();

        CGLFlushDrawable(nativeGraphicsContext);

        CGLUnlockContext(nativeGraphicsContext);
    }

    void CGLRenderer::render(seconds interpolation)
    {
        CGLLockContext(nativeGraphicsContext);

        OpenGlRenderer::render(interpolation);

        CGLFlushDrawable(nativeGraphicsContext);
        
        CGLUnlockContext(nativeGraphicsContext);
    }

}}