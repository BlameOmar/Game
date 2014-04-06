/**************************************************************************************************
 * @file    Component.h
 * @date    2014-04-02
 * @brief   Abstract Component Structure
 * @details <#Detailed Description#>
 **************************************************************************************************/

#pragma once

#include "types.h"

namespace evansbros {
    namespace game {
        class Component {
            friend class ComponentManager;

        public:
            Component() = default;
            Component(UniqueID entity_uid);

            virtual ~Component() = default;

            UniqueID getUID() const;
            UniqueID getEntityUID() const;
        private:
            UniqueID uid { 0 };
            UniqueID entity_uid { 0 };
        };
    }
}