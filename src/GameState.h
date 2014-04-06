/**************************************************************************************************
 * Title:         GameState.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-18
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "vector2.h"
#include "vector3.h"
#include "Array.h"
#include "TileMap.h"
#include <unordered_map>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SpatialComponent.h"

namespace evansbros {
    namespace game {

        struct GameState {
            UniqueID player1;
            UniqueID player2;
            UniqueID camera;

            GameState() : entityManager(componentManager) {}

            ComponentManager componentManager;
            EntityManager entityManager;
            Array<Entity> entities;

            TileMap currentTileMap;

        private:
            std::unordered_map<ID, Index> entityLookupTable;
            std::unordered_map<ID, ID> entityToSpatialComponentMap;
        public:
            void updateSpatialComponents(seconds dTime);

            ID createHuman(math::vector2 position);
            ID createCamera(math::vector2 position);
        };

    }
}