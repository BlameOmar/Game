/**************************************************************************************************
 * Title:         GameState.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-18
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameState.h"

namespace evansbros { namespace game {

    void SpatialState::incrementVelocity(math::vector3 delta) {
        velocity += delta;
        if (speed() > max_speed) {
            velocity = max_speed * velocity / velocity.magnitude();
        }
    }

    real SpatialState::speed() {
        return velocity.magnitude();
    }

} }