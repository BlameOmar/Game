/**************************************************************************************************
 * Title:         CGLRenderer.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-15
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "CGLRenderer.h"

namespace evansbros { namespace graphics {

    CGLRenderer::CGLRenderer() {
        nativeGraphicsContext = CGLGetCurrentContext();
    }

    void CGLRenderer::init()
    {
        CGLLockContext(nativeGraphicsContext);

        CGLSetCurrentContext(nativeGraphicsContext);

        CGLUnlockContext(nativeGraphicsContext);
    }

    void CGLRenderer::render(seconds interpolation)
    {
        CGLLockContext(nativeGraphicsContext);

        OpenGLRenderer::render(interpolation);

        CGLFlushDrawable(nativeGraphicsContext);
        
        CGLUnlockContext(nativeGraphicsContext);
    }

    void CGLRenderer::loadGPU_Textures()
    {
        CGLLockContext(nativeGraphicsContext);

        OpenGLRenderer::loadGPU_Textures();

        CGLUnlockContext(nativeGraphicsContext);
    }

    void CGLRenderer::loadGPU_Textures(const std::vector<string> & textureNames)
    {
        CGLLockContext(nativeGraphicsContext);

        OpenGLRenderer::loadGPU_Textures(textureNames);

        CGLUnlockContext(nativeGraphicsContext);
    }

    void CGLRenderer::unloadGPU_Textures()
    {
        CGLLockContext(nativeGraphicsContext);

        OpenGLRenderer::unloadGPU_Textures();

        CGLUnlockContext(nativeGraphicsContext);
    }

    void CGLRenderer::unloadGPU_Textures(const std::vector<string> & textureNames)
    {
        CGLLockContext(nativeGraphicsContext);

        OpenGLRenderer::unloadGPU_Textures(textureNames);

        CGLUnlockContext(nativeGraphicsContext);
    }

}}