/**************************************************************************************************
 * Title:         SpatialComponent.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "Component.h"
#include "vector2.h"

namespace evansbros {
    namespace game {
        class SpatialComponent : public Component {
        public:
            math::vector2 position;
            math::vector2 velocity;

            SpatialComponent() = default;
            SpatialComponent(natural entity_id) : Component(entity_id) {}

            real speed() const;
        };

    }
}


