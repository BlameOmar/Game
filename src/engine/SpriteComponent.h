/**************************************************************************************************
 * @file    SpriteComponent.h
 * @date    2014-04-11
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **************************************************************************************************/

#pragma once

#include "Component.h"

#include "Quad.h"

namespace evansbros {
    namespace game {
        class SpriteComonent : public Component {
        public:
            string texture;
            graphics::Quad boundingBox { graphics::Quad::COLORLESS_CENTERED_UNIT_SQUARE };
            
            SpriteComonent() = default;
            SpriteComonent(UniqueID entityUID) : Component(entityUID) {}
        };
    }
}