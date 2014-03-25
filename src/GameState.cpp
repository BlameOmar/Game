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

        void SpatialState::incrementVelocity(math::vector3 delta) {
            velocity += delta;
            if (speed() > max_speed) {
                velocity = max_speed * velocity / velocity.magnitude();
            }
        }

        real SpatialState::speed() {
            return velocity.magnitude();
        }

        ID GameState::createHuman(math::vector2 position)
        {
            ID entity_id = createEntity();
            ID spatialComponent_id = addSpatialComponentToEntity(entity_id);
            getSpatialComponentWithID(spatialComponent_id).position = position;

            return entity_id;
        }

        ID GameState::createCamera(math::vector2 position)
        {
            ID entity_id = createEntity();
            ID spatialComponent_id = addSpatialComponentToEntity(entity_id);
            getSpatialComponentWithID(spatialComponent_id).position = position;

            return entity_id;
        }


        void GameState::updateSpatialComponents(seconds dTime)
        {
            for (SpatialComponent & component : spatialComponents) {
                component.position += component.velocity * dTime.count();
                if (component.speed() < 0.0625) {
                    component.velocity = {0.0, 0.0};
                }
            }
        }

    }
}