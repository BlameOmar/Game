/**************************************************************************************************
 * Title:         GameState.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-18
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include <set>

#include "vector2.h"
#include "TileMap.h"

#include "EntityManager.h"
#include "ComponentManager.h"

namespace evansbros {
    namespace game {

        struct GameState {
            ComponentManager componentManager;
            EntityManager entityManager;

            std::set<std::pair<UniqueID, UniqueID>> collidingEntities;

            TileMap currentTileMap;

            UniqueID player1;
            UniqueID player2;
            UniqueID camera;

            GameState() : entityManager(componentManager) {}
        public:
            void updateSpatialComponents(seconds dTime);
            void detectCollisions();
            void resolveCollisions();

            UniqueID createHuman(math::vector2 position);
            UniqueID createBall(math::vector2 position);
            UniqueID createCamera(math::vector2 position);
        };

    }
}