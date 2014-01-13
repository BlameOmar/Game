/**************************************************************************************************
 * Title:         GameSystem_AssetLoading.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameSystem.h"
#include "utilities.h"

namespace evansbros { namespace game {

    using graphics::TextureQuality;

    void GameSystem::loadTextures()
    {
        loadTexture("test");
        loadTexture("grass");
        loadTexture("dirt");
        loadTexture("cobblestone");
        loadTexture("water");
        loadTexture("sand");
    }

    void GameSystem::loadTexture(string textureName)
    {
        PixelData texture;

        texture = decodePNGData(loadAsset("textures/" + textureName + "_nHD.png"));
        textures[TextureQuality::nHD][textureName] = texture;

        texture = decodePNGData(loadAsset("textures/" + textureName + "_qHD.png"));
        textures[TextureQuality::qHD][textureName] = texture;

        texture = decodePNGData(loadAsset("textures/" + textureName + "_HD.png"));
        textures[TextureQuality::HD][textureName] = texture;

        texture = decodePNGData(loadAsset("textures/" + textureName + "_FHD.png"));
        textures[TextureQuality::FULL_HD][textureName] = texture;

        texture = decodePNGData(loadAsset("textures/" + textureName + "_HD@2x.png"));
        textures[TextureQuality::QUAD_HD][textureName] = texture;

        texture = decodePNGData(loadAsset("textures/" + textureName + "_FHD@2x.png"));
        textures[TextureQuality::ULTRA_HD][textureName] = texture;
    }

} }
