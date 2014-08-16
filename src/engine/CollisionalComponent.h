/**************************************************************************************************
 * @file    CollisionalComponent.h
 * @date    2014-04-09
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **************************************************************************************************/

#pragma once

#include "Component.h"
#include "vector2.h"
#include "geometry.h"

namespace evansbros {
    namespace game {
        class CollisionalComponent : public Component {
        public:
            natural collisionGroupUID { 0 };

            enum class Type {
                Undefined,
                Circular,
                Linear,
            } type { Type::Undefined };

            union CollisionalComponentData {
                math::vector2 offset;
                math::geometry::Circle circularData;
                math::geometry::LineSegment linearData;

                CollisionalComponentData() : offset{ 0.0, 0.0 } { /* Nothing to do here */ };
                CollisionalComponentData(math::geometry::Circle circle) : circularData{ circle } { /* Nothing to do here */ }
                CollisionalComponentData(math::geometry::LineSegment lineSegment) : linearData { lineSegment } { /* Nothing to do here */ }
            } data;

            CollisionalComponent() = default;
            CollisionalComponent(UniqueID entityUID) : Component(entityUID) {}
            CollisionalComponent(UniqueID entityUID, math::geometry::Circle circle)
                : Component(entityUID), type(Type::Circular), data(circle) { /* Nothing to do here */ }
            CollisionalComponent(UniqueID entityUID, math::geometry::LineSegment lineSegment)
                : Component(entityUID), type(Type::Linear), data(lineSegment) { /* Nothing to do here */ }
        };
    }
}