/**************************************************************************************************
 * Title:         SpatialComponent.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"
#include "vector2.h"

namespace evansbros {
    namespace game {
        struct SpatialComponent {

            static ID next_id;

            math::vector2 position;
            math::vector2 velocity;

            ID id = 0;
            ID entity_id = 0;

            SpatialComponent() = default;
            SpatialComponent(natural id, natural entity_id) : id(id), entity_id(entity_id) {}

            real speed() const;
        };

    }
}


