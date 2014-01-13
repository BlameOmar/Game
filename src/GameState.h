/**************************************************************************************************
 * Title:         GameState.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-18
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "vector3.h"
#include "TileMap.h"

namespace evansbros { namespace game {

    struct SpatialState {
        math::vector3 position;
        math::vector3 velocity;

        void incrementVelocity(math::vector3 delta);

        real speed();

        real max_speed = 4;
    };

    struct GameState {
        SpatialState p1State;
        SpatialState p2State;
        SpatialState cameraState;

        TileMap currentTileMap;
    };

} }