/**************************************************************************************************
 * Title:         CGLRenderer.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-15
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "OpenGLRenderer.h"

#include <OpenGL/OpenGL.h>

namespace evansbros {
    namespace graphics {

        class CGLRenderer : public OpenGLRenderer {
        private:
            CGLContextObj nativeGraphicsContext;
        public:
            CGLRenderer();

            void init();
            void render(seconds interpolation);

            void loadGPU_Textures();
            void loadGPU_Textures(const std::vector<string> & textureNames);

            void unloadGPU_Textures();
            void unloadGPU_Textures(const std::vector<string> & textureNames);
        };
        
    }
}
