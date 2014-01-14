//
//  CGLRenderer.h
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/15/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#pragma once

#include "OpenGLRender.h"

#include <OpenGL/OpenGL.h>

namespace evansbros {
    namespace graphics {

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
        
    }
}
