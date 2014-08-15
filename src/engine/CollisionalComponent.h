/**************************************************************************************************
 * @file    CollisionalComponent.h
 * @date    2014-04-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **************************************************************************************************/

#pragma once

#include "Component.h"
#include "vector2.h"

namespace evansbros {
    namespace game {
        class CollisionalComponent : public Component {
        public:
            math::vector2 offset;
            real radius { 0.5 };
            natural collisionGroupUID { 0 };
            
            CollisionalComponent() = default;
            CollisionalComponent(UniqueID entityUID) : Component(entityUID) {}
            CollisionalComponent(UniqueID entityUID, math::vector2 offset, real radius) : Component(entityUID), offset(offset), radius(radius) {}
        };
    }
}