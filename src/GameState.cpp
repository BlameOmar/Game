/**************************************************************************************************
 * Title:         GameState.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-18
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameState.h"

namespace evansbros {
    namespace game {

        ID GameState::createHuman(math::vector2 position)
        {
            UniqueID entityUID = entityManager.createEntity();
            UniqueID spatialComponentUID = entityManager.addToEntity<SpatialComponent>(entityUID);
            componentManager.get<SpatialComponent>(spatialComponentUID).position = position;

            return entityUID;
        }

        ID GameState::createCamera(math::vector2 position)
        {
            UniqueID entityUID = entityManager.createEntity();
            UniqueID spatialComponentUID = entityManager.addToEntity<SpatialComponent>(entityUID);
            componentManager.get<SpatialComponent>(spatialComponentUID).position = position;

            return entityUID;
        }


        void GameState::updateSpatialComponents(seconds dTime)
        {
            size_t count = componentManager.count<SpatialComponent>();
            SpatialComponent * components = componentManager.getAll<SpatialComponent>();
            for (size_t i = 0; i < count; ++i) {
                SpatialComponent & component = components[i];
                component.position += component.velocity * dTime.count();
                if (component.speed() < 0.0625) {
                    component.velocity = {0.0, 0.0};
                }
            }
        }

    }
}