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

#include "Entity.h"
#include "SpatialComponent.h"


namespace evansbros {
    namespace game {

        struct SpatialState {
            math::vector3 position;
            math::vector3 velocity;

            void incrementVelocity(math::vector3 delta);

            real speed();

            real max_speed = 4;
        };

        struct GameState {
            ID player1;
            ID player2;
            ID camera;

            Array<Entity> entities;
            Array<SpatialComponent> spatialComponents;

            TileMap currentTileMap;
        private:
            std::unordered_map<ID, Index> entityLookupTable;
            std::unordered_map<ID, Index> spatialComponentLookupTable;

            std::unordered_map<ID, ID> entityToSpatialComponentMap;

        public:

            /* Entity Management */
            ID createEntity();

            Entity & getEntityWithID(ID entity_id);
            const Entity & getEntityWithID(ID entity_id) const;

            bool existsEntityWithID(ID entity_id) const;

            void destroyEntityWithID(ID entity_id);

            /* Spatial Component Management */
            ID addSpatialComponentToEntity(ID entity_id);

            SpatialComponent & getSpatialComponentWithID(ID component_id);
            const SpatialComponent & getSpatialComponentWithID(ID component_id) const;

            SpatialComponent & getSpatialComponentWithEntityID(ID entity_id);
            const SpatialComponent & getSpatialComponentWithEntityID(ID entity_id) const;

            Entity & getOwnerOfSpatialComponent(ID component_id);
            const Entity & getOwnerOfSpatialComponent(ID component_id) const;

            bool existsSpatialComponentWithID(ID component_id) const;
            bool existsSpatialComponentWithEntityID(ID entity_id) const;

            void destroySpatialComponentWithID(ID component_id);

            void updateSpatialComponents(seconds dTime);

            ID createHuman(math::vector2 position);
            ID createCamera(math::vector2 position);
        };

    }
}