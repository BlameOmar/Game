/**************************************************************************************************
 * Title:         Renderer.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-15
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "GameState.h"
#include "types.h"
#include "PixelData.h"
#include "Color.h"
#include "Quad.h"

#include <map>

namespace evansbros { namespace graphics {

    using math::vector3;
    using game::GameState;

    enum class RenderType {
        CGL_RENDERER,
        XGL_RENDERER,
        DIRECT3D_9_RENDERER,
        DIRECT3D_11_RENDERER,
        MANTLE_RENDERER
    };

    enum class TextureQuality {
        ULTRA_HD,
        QUAD_HD,
        FULL_HD,
        HD,
        qHD,
        nHD,
    };

    class Renderer {
    public:
        virtual void setup() = 0;
        virtual void render(seconds interpolation) = 0;
        virtual void resizeViewport(real width, real height) = 0;

        void setGameState(const GameState *gameState);

        void setTextures(std::map<TextureQuality, std::map<string, PixelData>> * textures);


        void setTextureQuality(TextureQuality quality);

        virtual void loadGPU_Textures() = 0;
        virtual void loadGPU_Textures(const std::vector<string> & textureNames) = 0;

        virtual void unloadGPU_Textures() = 0;
        virtual void unloadGPU_Textures(const std::vector<string> & textureNames) = 0;

        void reloadGPU_Textures();

    protected:
        const GameState *gameState;

        TextureQuality textureQuality = TextureQuality::HD;
        const std::map<TextureQuality, std::map<string, PixelData>> *textures;

        void drawTileMap();

        virtual void drawQuads(Quad quad, string texture, std::vector<vector3> positions) = 0;
    };

} }
