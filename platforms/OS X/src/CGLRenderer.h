//
//  CGLRenderer.h
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/15/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#ifndef __OpenGL_Practice__CGLRenderer__
#define __OpenGL_Practice__CGLRenderer__

#include "OpenGLRender.h"

#import <OpenGL/OpenGL.h>

#include <atomic>

namespace evansbros { namespace graphics {

    class CGLRenderer : public OpenGlRenderer {
    private:
        CGLContextObj nativeGraphicsContext;
    public:
        CGLRenderer();
        ~CGLRenderer();

        CGLContextObj getNativeGraphicsContext();
        void setNativeGraphicsContext(CGLContextObj context);

        void setup();
        void render(seconds interpolation);
    };
}}

#endif /* defined(__OpenGL_Practice__CGLRenderer__) */
