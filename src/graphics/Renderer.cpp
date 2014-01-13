/**************************************************************************************************
 * Title:         Renderer.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-15
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "Renderer.h"

namespace evansbros { namespace graphics {

    void Renderer::setGameState(const GameState *gameState)
    {
        this->gameState = gameState;
    }

    void Renderer::setTextures(std::map<TextureQuality, std::map<string, PixelData>> *textures)
    {
        this->textures = textures;
    }

    void Renderer::setTextureQuality(TextureQuality quality) {
        if (textureQuality != quality) {
            textureQuality = quality;
            reloadGPU_Textures();
        }
    }

    void Renderer::reloadGPU_Textures() {
        unloadGPU_Textures();
        loadGPU_Textures();
    }

    void Renderer::drawTileMap() {
        const game::TileMap &tileMap = gameState->currentTileMap;
        std::map<string, std::vector<vector3>> tiles;

        for (natural x = 0; x < tileMap.width; ++x) {
            for (natural y = 0; y < tileMap.height; ++y) {
                tiles[tileMap.textureDefinitions.at(tileMap(x, tileMap.height - y - 1))].push_back({x - tileMap.width / 2.0, y - tileMap.height / 2.0, -1.0});
            }
        }

        Quad uncoloredQuad({{0.0, 0.0}, Color()}, {{1.0, 0.0}, Color()}, {{1.0, 1.0}, Color()}, {{0.0, 1.0}, Color()});
        for (auto tile : tiles) {
            drawQuads(uncoloredQuad, tile.first, tile.second);
        }
    }

} }
