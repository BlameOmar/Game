//
//  SpatialComponent.cpp
//  Game
//
//  Created by Omar Stefan Evans on 12/7/13.
//
//

#include "SpatialComponent.h"

using evansbros::math::vector3;

namespace evansbros { namespace game { namespace engine {

    void SpatialComponent::update(seconds dTime) {
        position += velocity * dTime.count();
    }

    vector3 SpatialComponent::getPosition() const
    {
        return position;
    }

    vector3 SpatialComponent::getVelocity() const
    {
        return velocity;
    }

} } }
